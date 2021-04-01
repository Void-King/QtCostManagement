#pragma once

#include <Windows.h>
#include <qthread.h>

enum AccentState
{
	ACCENT_DISABLED = 0,
	ACCENT_ENABLE_GRADIENT = 1,
	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
	ACCENT_ENABLE_BLURBEHIND = 3,
	ACCENT_INVALID_STATE = 4
};
struct AccentPolicy
{
	AccentState AccentState;
	int AccentFlags;
	int GradientColor;
	int AnimationId;
};
enum WindowCompositionAttribute
{
	WCA_UNDEFINED = 0,
	WCA_NCRENDERING_ENABLED = 1,
	WCA_NCRENDERING_POLICY = 2,
	WCA_TRANSITIONS_FORCEDISABLED = 3,
	WCA_ALLOW_NCPAINT = 4,
	WCA_CAPTION_BUTTON_BOUNDS = 5,
	WCA_NONCLIENT_RTL_LAYOUT = 6,
	WCA_FORCE_ICONIC_REPRESENTATION = 7,
	WCA_EXTENDED_FRAME_BOUNDS = 8,
	WCA_HAS_ICONIC_BITMAP = 9,
	WCA_THEME_ATTRIBUTES = 10,
	WCA_NCRENDERING_EXILED = 11,
	WCA_NCADORNMENTINFO = 12,
	WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
	WCA_VIDEO_OVERLAY_ACTIVE = 14,
	WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
	WCA_DISALLOW_PEEK = 16,
	WCA_CLOAK = 17,
	WCA_CLOAKED = 18,
	WCA_ACCENT_POLICY = 19,
	WCA_FREEZE_REPRESENTATION = 20,
	WCA_EVER_UNCLOAKED = 21,
	WCA_VISUAL_OWNER = 22,
	WCA_LAST = 23
};
struct WindowCompositionAttributeData
{
	WindowCompositionAttribute Attribute;
	int * Data;
	int SizeOfData;
};

typedef int* (*pfun)(HWND hwnd, WindowCompositionAttributeData *data);

void Acrylic(HWND& hWnd)
{
	HMODULE hUser = GetModuleHandle(L"user32.dll");

	if (hUser) {
		pfun setWindowCompositionAttribute =
			(pfun)GetProcAddress(hUser, "SetWindowCompositionAttribute");
		if (setWindowCompositionAttribute) {
			AccentPolicy accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
			WindowCompositionAttributeData data;
			data.Attribute = WCA_ACCENT_POLICY;
			data.Data = reinterpret_cast<int *>(&accent);
			data.SizeOfData = sizeof(accent);
			setWindowCompositionAttribute(hWnd, &data);
		}
	}
}