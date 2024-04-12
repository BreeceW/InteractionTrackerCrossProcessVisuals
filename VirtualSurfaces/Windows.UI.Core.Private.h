#pragma once

#include <Windows.h>

enum COREINPUT_TYPE : unsigned int
{
	CI_INDEPENDENT_INPUT = 0x0,
	CI_COMPONENT_INPUT = 0x1,
};

enum COREINPUT_POINTER_TYPE : unsigned int
{
	CIPT_NONE = 0x0,
	CIPT_TOUCH = 0x1,
	CIPT_PEN = 0x2,
	CIPT_MOUSE = 0x4,
	CIPT_KEYBOARD = 0x8,
};

enum COREINPUT_FLAGS : unsigned int
{
	CIF_NONE = 0x0,
	CIF_ENSURE_AGILE_HANDLERS = 0x1,
};

// Ordinal: 1600 (0x640), Dll: Windows.UI.dll
HRESULT PrivateCreateCoreInput(COREINPUT_TYPE InputType, COREINPUT_POINTER_TYPE PointerTypes, COREINPUT_FLAGS Flags, const GUID& riid, void** ppv);