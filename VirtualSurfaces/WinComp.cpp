//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
// THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//*********************************************************

#include "stdafx.h"
#include "WinComp.h"
#include "windows.ui.composition.interop.h"

//
//  FUNCTION: EnsureDispatcherQueue
//
//  PURPOSE: It is necessary for a DisptacherQueue to be available on the same thread in which
//	the Compositor runs on. Events for the Compositor are fired using this DispatcherQueue
//
DispatcherQueueController WinComp::EnsureDispatcherQueue()
{
	namespace abi = ABI::Windows::System;

	DispatcherQueueOptions options
	{
		sizeof(DispatcherQueueOptions),
		DQTYPE_THREAD_CURRENT,
		DQTAT_COM_ASTA
	};

	DispatcherQueueController controller{ nullptr };
	check_hresult(CreateDispatcherQueueController(options, reinterpret_cast<abi::IDispatcherQueueController**>(put_abi(controller))));

	return controller;
}

//
//  FUNCTION:Initialize
//
//  PURPOSE: Initializes all the key member variables, including the Compositor. This sample hosts directX content inside a visual
//
void WinComp::Initialize(HWND hwnd)
{
	namespace abi = ABI::Windows::UI::Composition;

	m_window = hwnd;
	Compositor compositor;
	m_compositor = compositor;
	DirectXTileRenderer* dxRenderer = new DirectXTileRenderer();
	dxRenderer->Initialize(m_compositor, TileDrawingManager::TILESIZE, TileDrawingManager::MAXSURFACESIZE);
	m_TileDrawingManager.SetRenderer(dxRenderer);

}

void WinComp::TryRedirectForManipulation(PointerPoint pp)
{
	//Redirecting the Pointer input for manipulation by the InteractionTracker
	m_interactionSource.TryRedirectForManipulation(pp);
}

void WinComp::TryUpdatePositionBy(float3 const& amount)
{
	m_tracker.TryUpdatePositionBy(amount);
}
//
//  FUNCTION: PrepareVisuals
//
//  PURPOSE: Creates the Visual tree and hooks it up to the desktopWindowTarget
//
void WinComp::PrepareVisuals(HANDLE handle)
{
	auto partner = m_compositor.try_as<ICompositorPartner>();

	partner->OpenSharedTargetFromHandle(handle, visualTarget.put());

	namespace abi = ABI::Windows::UI::Composition::Desktop;

	//Creates a DesktopWindowTarget that can host Windows.UI.Composition Visual tree inside an HWnd
	auto interop = m_compositor.as<abi::ICompositorDesktopInterop>();
	check_hresult(interop->CreateDesktopWindowTarget(m_window, true, reinterpret_cast<abi::IDesktopWindowTarget**>(put_abi(m_target))));

	auto root = m_compositor.CreateSpriteVisual();
	//Create a background with Gray color brush.
	root.Brush(m_compositor.CreateColorBrush({ 0xFF, 0xFE, 0xFE , 0xFE }));

	m_target.Root(root);

	auto visuals = root.Children();
	AddD2DVisual(visuals, 0.0f, 0.0f);

	SpriteVisual redirectVisual = m_compositor.CreateSpriteVisual();
	CompositionVisualSurface visualSurface = m_compositor.CreateVisualSurface();
	CompositionSurfaceBrush surfaceBrush = m_compositor.CreateSurfaceBrush(visualSurface);

	visualSurface.SourceVisual(root);
	surfaceBrush.Stretch(CompositionStretch::None);
	redirectVisual.Brush(surfaceBrush);

	auto size = m_contentVisual.Size();
	redirectVisual.Size(size);
	visualSurface.SourceSize(size);

	ExpressionAnimation sizeAnim = m_compositor.CreateExpressionAnimation(L"rootVisual.Size");
	sizeAnim.SetReferenceParameter(L"rootVisual", m_contentVisual);

	redirectVisual.StartAnimation(L"Size", sizeAnim);
	visualSurface.StartAnimation(L"SourceSize", sizeAnim);

	// Apparently it's not possible to use a SpriteVisual with a CompositionVisualSurface brush
	// (or CompositionSurfaceBrush in general?) as VisualInteractionSource, so we create a transparent SpriteVisual
	// with a simple CompositionColorBrush on top of it and use it as VisualInteractionSource instead.
	this->redirectVisual = m_compositor.CreateSpriteVisual();
	this->redirectVisual.RelativeSizeAdjustment({ 1, 1 });
	this->redirectVisual.Brush(m_compositor.CreateColorBrush({ 0x0, 0x0, 0x0, 0x0 }));
	redirectVisual.Children().InsertAtTop(this->redirectVisual);

	visualTarget->SetRoot(reinterpret_cast<ABI::Windows::UI::Composition::IVisual*>(winrt::get_abi(redirectVisual)));

	Windows::System::Threading::WorkItemHandler workItemHandler([this, redirectVisual](Windows::Foundation::IAsyncAction const&)
	{
		CoreIndependentInputSource source{ nullptr };
		CoreIndependentInputSourceController controller{ nullptr };

		if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent(winrt::name_of<CoreIndependentInputSourceController>()))
		{
			controller = CoreIndependentInputSourceController::CreateForVisual(redirectVisual);
			controller.SetControlledInput(CoreInputDeviceTypes::Touch | CoreInputDeviceTypes::Pen);
			source = controller.Source();
		}
		else
		{
			HMODULE winui = GetModuleHandle(L"Windows.UI.dll");
			if (!winui) winui = LoadLibrary(L"Windows.UI.dll");

			if (winui)
			{
				auto CreateCoreInput = (decltype(&PrivateCreateCoreInput))GetProcAddress(winui, MAKEINTRESOURCEA(0x640));

				if (CreateCoreInput)
				{
					auto result = CreateCoreInput(CI_INDEPENDENT_INPUT, (COREINPUT_POINTER_TYPE)(CIPT_TOUCH | CIPT_PEN), CIF_NONE, winrt::guid_of<ICoreInputSourceBase>(), winrt::put_abi(source));

					if (SUCCEEDED(result))
					{
						auto sourceInterop = source.try_as<ICoreInputInterop>();
						if (sourceInterop)
							sourceInterop->SetInputSource((::IUnknown*)winrt::get_abi(redirectVisual));
					}
				}
			}
		}

		if (source)
		{
			source.PointerPressed({ this, &WinComp::OnRedirectVisualPointerPressed });
			source.Dispatcher().ProcessEvents(Windows::UI::Core::CoreProcessEventsOption::ProcessUntilQuit);
		}
	});

	Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);
}

//
//  FUNCTION: AddD2DVisual
//
//  PURPOSE: Creates a SurfaceBrush to host Direct2D content in this visual.
//
void WinComp::AddD2DVisual(VisualCollection const& visuals, float x, float y)
{
	auto compositor = visuals.Compositor();
	m_contentVisual = compositor.CreateSpriteVisual();
	m_contentVisual.Brush(m_TileDrawingManager.GetRenderer()->getSurfaceBrush());

	m_contentVisual.Size(GetWindowSize());
	m_contentVisual.Offset({ x, y, 0.0f, });

	visuals.InsertAtTop(m_contentVisual);
}

//
//  FUNCTION: UpdateViewPort
//
//  PURPOSE: This is called when the Viewport size has changed, because of events like maximize, resize window etc.
//
void WinComp::UpdateViewPort(boolean changeContentVisual)
{
	//return if the m_window hasn't been set.
	if(m_window!=NULL){
		RECT windowRect;
		::GetWindowRect(m_window, &windowRect);
		Size windowSize;
		windowSize.Height = (windowRect.bottom-windowRect.top)/m_lastTrackerScale;
		windowSize.Width = (windowRect.right-windowRect.left)/m_lastTrackerScale;

		if(changeContentVisual){
			m_contentVisual.Size(windowSize);
		}
		m_TileDrawingManager.UpdateViewportSize(windowSize);
		m_TileDrawingManager.UpdateVisibleRegion(m_lastTrackerPosition/m_lastTrackerScale);
	}
}

//
//  FUNCTION: GetWindowSize
//
//  PURPOSE: Helper function for get the size of the HWnd.
//
Size WinComp::GetWindowSize()
{
	RECT windowRect;
	::GetWindowRect(m_window, &windowRect);
	return Size({ (float)(windowRect.right - windowRect.left), (float)(windowRect.bottom - windowRect.top) });
}

void WinComp::OnRedirectVisualPointerPressed(IInspectable const& sender, PointerEventArgs const& args)
{
	//Redirecting the Pointer input for manipulation by the InteractionTracker
	m_interactionSource2.TryRedirectForManipulation(args.CurrentPoint());
}

//
//  FUNCTION: StartAnimation
//
//  PURPOSE: Use CompositionPropertySet and Expression Animations to manipulate the Virtual Surface.
//
void WinComp::StartAnimation(CompositionSurfaceBrush brush)
{
	m_animatingPropset = m_compositor.CreatePropertySet();
	m_animatingPropset.InsertScalar(L"xcoord", 1.0f);
	m_animatingPropset.StartAnimation(L"xcoord", m_moveSurfaceExpressionAnimation);

	m_animatingPropset.InsertScalar(L"ycoord", 1.0f);
	m_animatingPropset.StartAnimation(L"ycoord", m_moveSurfaceUpDownExpressionAnimation);

	m_animatingPropset.InsertScalar(L"scale", 1.0f);
	m_animatingPropset.StartAnimation(L"scale", m_scaleSurfaceUpDownExpressionAnimation);

	m_animateMatrix = m_compositor.CreateExpressionAnimation(L"Matrix3x2(props.scale, 0.0, 0.0, props.scale, props.xcoord, props.ycoord)");
	m_animateMatrix.SetReferenceParameter(L"props", m_animatingPropset);

	brush.StartAnimation(L"TransformMatrix", m_animateMatrix);
}

//
//  FUNCTION: ConfigureInteraction
//
//  PURPOSE: Configure InteractionTracker on this visual, to enable touch, PTP and mousewheel based interactions.
//
void WinComp::ConfigureInteraction()
{
	m_interactionSource = VisualInteractionSource::Create(m_contentVisual);
	m_interactionSource.PositionXSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource.PositionYSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource.ScaleSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource.ManipulationRedirectionMode(VisualInteractionSourceRedirectionMode::CapableTouchpadAndPointerWheel);

	m_interactionSource2 = VisualInteractionSource::Create(redirectVisual);
	m_interactionSource2.PositionXSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource2.PositionYSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource2.ScaleSourceMode(InteractionSourceMode::EnabledWithInertia);
	m_interactionSource2.ManipulationRedirectionMode(VisualInteractionSourceRedirectionMode::CapableTouchpadAndPointerWheel);

	m_tracker = InteractionTracker::CreateWithOwner(m_compositor, *this);
	m_tracker.InteractionSources().Add(m_interactionSource);
	m_tracker.InteractionSources().Add(m_interactionSource2);

	m_moveSurfaceExpressionAnimation = m_compositor.CreateExpressionAnimation(L"-tracker.Position.X");
	m_moveSurfaceExpressionAnimation.SetReferenceParameter(L"tracker", m_tracker);

	m_moveSurfaceUpDownExpressionAnimation = m_compositor.CreateExpressionAnimation(L"-tracker.Position.Y");
	m_moveSurfaceUpDownExpressionAnimation.SetReferenceParameter(L"tracker", m_tracker);

	m_scaleSurfaceUpDownExpressionAnimation = m_compositor.CreateExpressionAnimation(L"tracker.Scale");
	m_scaleSurfaceUpDownExpressionAnimation.SetReferenceParameter(L"tracker", m_tracker);

	m_tracker.MinPosition(float3(0, 0, 0));
	m_tracker.MaxPosition(float3(TileDrawingManager::MAXSURFACESIZE, TileDrawingManager::MAXSURFACESIZE, 0));

	m_tracker.MinScale(0.2f);
	m_tracker.MaxScale(3.0f);

	StartAnimation(m_TileDrawingManager.GetRenderer()->getSurfaceBrush());
}

// interactionTrackerowner methods.

void WinComp::CustomAnimationStateEntered(InteractionTracker sender, InteractionTrackerCustomAnimationStateEnteredArgs args)
{
}

void WinComp::IdleStateEntered(InteractionTracker sender, InteractionTrackerIdleStateEnteredArgs args)
{
	if (m_zooming)
	{
		//dont update the content visual, because the window size hasnt changed.
		UpdateViewPort( false);
	}
	m_zooming = false;
}

void WinComp::InertiaStateEntered(InteractionTracker sender, InteractionTrackerInertiaStateEnteredArgs args)
{
}

void WinComp::InteractingStateEntered(InteractionTracker sender, InteractionTrackerInteractingStateEnteredArgs args)
{

}

void WinComp::RequestIgnored(InteractionTracker sender, InteractionTrackerRequestIgnoredArgs args)
{
}

void WinComp::ValuesChanged(InteractionTracker sender, InteractionTrackerValuesChangedArgs args)
{
	if (m_lastTrackerScale == args.Scale())
	{
		m_TileDrawingManager.UpdateVisibleRegion(sender.Position()/m_lastTrackerScale);
	}
	else
	{
		// Don't run tilemanager during a zoom
		m_zooming = true;
	}

	m_lastTrackerScale = args.Scale();
	m_lastTrackerPosition = sender.Position();
}
