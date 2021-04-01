#ifndef WINMSGFILTER_H
#define WINMSGFILTER_H
#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <Windows.h>
#pragma comment(lib, "dwmapi")
#pragma comment(lib,"user32.lib")
#include <dwmapi.h>
#include <windowsx.h>

class WinMsgFilter :public QAbstractNativeEventFilter
{
public:
	WinMsgFilter() {};
	//过滤掉消息返回true，否则返回false
	bool nativeEventFilter(const QByteArray& eventType,
		void* message, long* result) override
	{
		MSG* pMsg = reinterpret_cast<MSG*>(message);

		switch (pMsg->message)
		{
			//去掉边框
		case WM_NCCALCSIZE:
		{
			*result = 0;
			return true;
			break;
		}
		//阴影
		case WM_ACTIVATE:
		{
			MARGINS margins = { 1,1,1,1 };
			HRESULT hr = S_OK;
			hr = DwmExtendFrameIntoClientArea(pMsg->hwnd, &margins);
			*result = hr;
			return true;
		}
		case WM_NCHITTEST:
		{
			//处理resize
			//标记只处理resize
			bool isResize = false;

			//鼠标点击的坐标
			POINT ptMouse = { GET_X_LPARAM(pMsg->lParam),
				GET_Y_LPARAM(pMsg->lParam) };
			//窗口矩形
			RECT rcWindow;
			GetWindowRect(pMsg->hwnd, &rcWindow);
			RECT rcFrame = { 0,0,0,0 };
			AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW
				& ~WS_CAPTION, FALSE, NULL);
			USHORT uRow = 1;
			USHORT uCol = 1;
			bool fOnResizeBorder = false;

			//确认鼠标指针是否在top或者bottom
			//顺带说一下屏幕坐标原点是左上角，窗体坐标原点也是左上角
			if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + 1)
			{
				fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
				uRow = 0;
				isResize = true;
			}
			else if (ptMouse.y < rcWindow.bottom &&
				ptMouse.y >= rcWindow.bottom - 5)
			{
				uRow = 2;
				isResize = true;
			}
			//确认鼠标指针是否在left或者right
			if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + 5)
			{
				uCol = 0; // left side
				isResize = true;
			}
			else if (ptMouse.x < rcWindow.right &&
				ptMouse.x >= rcWindow.right - 5)
			{
				uCol = 2; // right side
				isResize = true;
			}
			//检测是不是在标题栏上，右边预留出了45*3 = 135的宽度，
			//是留给关闭按钮、最大化、最小化的。
			if (ptMouse.x >= rcWindow.left &&
				ptMouse.x <= rcWindow.right - 80 &&
				ptMouse.y > rcWindow.top + 3 &&
				ptMouse.y <= rcWindow.top + 50)
			{
				*result = HTCAPTION;
				return true;
			}

			LRESULT hitTests[3][3] =
			{
				{ HTTOPLEFT,    fOnResizeBorder ?
				HTTOP : HTCAPTION, HTTOPRIGHT },
				{ HTLEFT,       HTNOWHERE,     HTRIGHT },
				{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
			};

			if (isResize == true)
			{
				*result = hitTests[uRow][uCol];
				return true;
			}
			else
			{
				return false;
			}

		}
		}

		//这里一定要返回false，否则是屏蔽所有消息了
		return false;
	}

};

#endif // WINMSGFILTER_H