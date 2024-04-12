#pragma once

#include <Windows.h>

enum COREINPUT_TYPE : unsigned __int32
{
	CI_INDEPENDENT_INPUT = 0x0,
	CI_COMPONENT_INPUT = 0x1,
};

enum COREINPUT_POINTER_TYPE : unsigned __int32
{
	CIPT_NONE = 0x0,
	CIPT_TOUCH = 0x1,
	CIPT_PEN = 0x2,
	CIPT_MOUSE = 0x4,
	CIPT_KEYBOARD = 0x8,
};

// Ordinal: 1600 (0x640), Dll: Windows.UI.dll
HRESULT PrivateCreateCoreInput(COREINPUT_TYPE InputType, COREINPUT_POINTER_TYPE PointerTypes, unsigned int Flags, const GUID& riid, void** ppv);