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
	//���˵���Ϣ����true�����򷵻�false
	bool nativeEventFilter(const QByteArray& eventType,
		void* message, long* result) override
	{
		MSG* pMsg = reinterpret_cast<MSG*>(message);

		switch (pMsg->message)
		{
			//ȥ���߿�
		case WM_NCCALCSIZE:
		{
			*result = 0;
			return true;
			break;
		}
		//��Ӱ
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
			//����resize
			//���ֻ����resize
			bool isResize = false;

			//�����������
			POINT ptMouse = { GET_X_LPARAM(pMsg->lParam),
				GET_Y_LPARAM(pMsg->lParam) };
			//���ھ���
			RECT rcWindow;
			GetWindowRect(pMsg->hwnd, &rcWindow);
			RECT rcFrame = { 0,0,0,0 };
			AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW
				& ~WS_CAPTION, FALSE, NULL);
			USHORT uRow = 1;
			USHORT uCol = 1;
			bool fOnResizeBorder = false;

			//ȷ�����ָ���Ƿ���top����bottom
			//˳��˵һ����Ļ����ԭ�������Ͻǣ���������ԭ��Ҳ�����Ͻ�
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
			//ȷ�����ָ���Ƿ���left����right
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
			//����ǲ����ڱ������ϣ��ұ�Ԥ������45*3 = 135�Ŀ�ȣ�
			//�������رհ�ť����󻯡���С���ġ�
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

		//����һ��Ҫ����false������������������Ϣ��
		return false;
	}

};

#endif // WINMSGFILTER_H