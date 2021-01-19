#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <string>

HWND    hWrelease;
HBITMAP hWreleaseImage;
HWND    hArelease;
HBITMAP hAreleaseImage;
HWND    hSrelease;
HBITMAP hSreleaseImage;
HWND    hDrelease;
HBITMAP hDreleaseImage;
HWND    hSPACErelease;
HBITMAP hSPACEreleaseImage;

HWND    hWdown;
HBITMAP hWdownImage;
HWND    hAdown;
HBITMAP hAdownImage;
HWND    hSdown;
HBITMAP hSdownImage;
HWND    hDdown;
HBITMAP hDdownImage;
HWND    hSPACEdown;
HBITMAP hSPACEdownImage;

void CreateControls(HWND hWnd);
void LoadImages();

LRESULT CALLBACK HookProc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
)
{
	KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
	unsigned int keyCode = hooked_key.vkCode;

	if (wParam == WM_KEYDOWN) {
		if (keyCode == 87) {
			ShowWindow(hWrelease, SW_HIDE);
		}
		if (keyCode == 65) {
			ShowWindow(hArelease, SW_HIDE);
		}
		if (keyCode == 83) {
			ShowWindow(hSrelease, SW_HIDE);
		}
		if (keyCode == 68) {
			ShowWindow(hDrelease, SW_HIDE);
		}
		if (keyCode == 32) {
			ShowWindow(hSPACErelease, SW_HIDE);
		}
	}
	else if(wParam == WM_KEYUP) {
		if (keyCode == 87) {
			ShowWindow(hWrelease, SW_SHOW);
		}
		if (keyCode == 65) {
			ShowWindow(hArelease, SW_SHOW);
		}
		if (keyCode == 83)  {
			ShowWindow(hSrelease, SW_SHOW);
		}
		if (keyCode == 68) {
			ShowWindow(hDrelease, SW_SHOW);
		}
		if (keyCode == 32) {
			ShowWindow(hSPACErelease, SW_SHOW);
		}
	}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	LRESULT hit;
	switch (message)
	{
	case WM_CREATE:
		LoadImages();
		CreateControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NCHITTEST:
		hit = DefWindowProc(hWnd, message, wParam, lParam);
		if (hit == HTCLIENT) hit = HTCAPTION;
		return hit;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Overlay";
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex)) {
		MessageBox(0, L"Error", L"Call to register class failed", NULL);
		return 1;
	}

	static TCHAR szWindowClass[] = _T("Overlay");
	static TCHAR szTitle[] = _T("Overlay App");

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT, CW_USEDEFAULT,
		320, 320,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME));

	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, RGB(255, 0, 0), 0, LWA_COLORKEY);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	UpdateWindow(hWnd);

	SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, hInstance, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void CreateControls(HWND hWnd) {
	hWdown = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 110, 0, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hWdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hWdownImage);
	ShowWindow(hWdown, SW_SHOW);
	hWrelease = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 110, 0, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hWrelease, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hWreleaseImage);
	ShowWindow(hWrelease, SW_SHOW);

	hAdown = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hAdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hAdownImage);
	ShowWindow(hAdown, SW_SHOW);
	hArelease = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hArelease, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hAreleaseImage);
	ShowWindow(hArelease, SW_SHOW);

	hSdown = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 110, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hSdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSdownImage);
	ShowWindow(hSdown, SW_SHOW);
	hSrelease = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 110, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hSrelease, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSreleaseImage);
	ShowWindow(hSrelease, SW_SHOW);

	hDdown = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 220, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hDdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDdownImage);
	ShowWindow(hDdown, SW_SHOW);
	hDrelease = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 220, 110, 100, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hDrelease, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDreleaseImage);
	ShowWindow(hDrelease, SW_SHOW);

	hSPACEdown = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 220, 320, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hSPACEdown, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSPACEdownImage);
	ShowWindow(hSPACEdown, SW_SHOW);
	hSPACErelease = CreateWindow(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 220, 320, 100, hWnd, NULL, NULL, NULL);
	SendMessageW(hSPACErelease, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSPACEreleaseImage);
	ShowWindow(hSPACErelease, SW_SHOW);
}

void LoadImages() {
	hWdownImage = (HBITMAP)LoadImageW(0, L"w.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hAdownImage = (HBITMAP)LoadImageW(0, L"a.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hSdownImage = (HBITMAP)LoadImageW(0, L"s.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hDdownImage = (HBITMAP)LoadImageW(0, L"d.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hSPACEdownImage = (HBITMAP)LoadImageW(0, L"space.bmp", IMAGE_BITMAP, 320, 100, LR_LOADFROMFILE);

	hWreleaseImage = (HBITMAP)LoadImageW(0, L"wr.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hAreleaseImage = (HBITMAP)LoadImageW(0, L"ar.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hSreleaseImage = (HBITMAP)LoadImageW(0, L"sr.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hDreleaseImage = (HBITMAP)LoadImageW(0, L"dr.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hSPACEreleaseImage = (HBITMAP)LoadImageW(0, L"spacer.bmp", IMAGE_BITMAP, 320, 100, LR_LOADFROMFILE);
}