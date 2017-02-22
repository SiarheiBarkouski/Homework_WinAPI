#include <windows.h>  
#include <string>
#include <tchar.h>

static TCHAR szWindowClass[] = TEXT("win32app");
static TCHAR szTitle[] = TEXT("SuperCOOLApp");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
typedef std::basic_string<TCHAR> tstring;
#ifdef UNICODE
#define to_tstring std::to_wstring
#endif

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
	)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			TEXT("Call to RegisterClassEx failed!"),
			TEXT("SuperCOOLApp"),
			NULL);
		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 400,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			TEXT("Call to CreateWindow failed!"),
			TEXT("SuperCOOLApp"),
			NULL);

		return 1;
	}


	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:

	{
						   HWND hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
						   if (hCalc)
						   {
							   BringWindowToTop(hCalc);
							   SetWindowText(hCalc, TEXT("MyAppCalculator"));
						   }
	}
		break;

	case WM_RBUTTONDOWN:
		WinExec("C:\\Windows\\system32\\calc.exe", SW_SHOWNORMAL);
		break;

	case WM_KEYDOWN:
	{
					   RECT r;
					   GetWindowRect(hWnd, &r);
					   if (wParam == VK_LEFT)
						   MoveWindow(hWnd, r.left - 10, r.top, r.right - r.left, r.bottom - r.top, TRUE);

					   else if (wParam == VK_RIGHT)
						   MoveWindow(hWnd, r.left + 10, r.top, r.right - r.left, r.bottom - r.top, TRUE);

					   else if (wParam == VK_UP)
						   MoveWindow(hWnd, r.left, r.top - 10, r.right - r.left, r.bottom - r.top, TRUE);

					   else if (wParam == VK_DOWN)
						   MoveWindow(hWnd, r.left, r.top + 10, r.right - r.left, r.bottom - r.top, TRUE);

					   else if (wParam == VK_RETURN)
						   MoveWindow(hWnd, 0, 0, 300, 300, TRUE);
	}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}
