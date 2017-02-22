#include <windows.h>
#include <vector>
#include <string>
#include <tchar.h>
#include <iostream>

static TCHAR szWindowClass[] = _TEXT("win32app");
static TCHAR szTitle[] = _TEXT("SuperCOOLApp");
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam);
void minimize(HWND hwnd);
void maximize(HWND hwnd);
static HWND Calc = 0;
static std::vector <HWND> buttons(100);
static int counter = 0;

typedef std::basic_string<TCHAR> tstring;
#ifdef UNICODE
#define to_tstring std::to_wstring
#endif


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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
			_TEXT("Call to RegisterClassEx failed!"),
			_TEXT("SuperCOOLApp"),
			NULL);
		return 1;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_TEXT("Call to CreateWindow failed!"),
			_TEXT("SuperCOOLApp"),
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


VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HDC hDCScreen = GetDC(NULL);
	int Horres = GetDeviceCaps(hDCScreen, HORZRES);
	int Vertres = GetDeviceCaps(hDCScreen, VERTRES);
	ReleaseDC(NULL, hDCScreen);

	RECT rhWnd;
	GetWindowRect(hWnd, &rhWnd);

	RECT rShellTray;
	HWND hShellTray = FindWindow(_TEXT("Shell_TrayWnd"), NULL);
	GetWindowRect(hShellTray, &rShellTray);

	static bool up = true, left = true;

	static int posX = 0;
	static int posY = 0;

	if (up == true && left == true)
	{
		SetWindowPos(hWnd, HWND_TOP, posX += 5, posY, 300, 300, SWP_SHOWWINDOW);
		if (rhWnd.right == Horres)
			left = false;
	}

	else if (up == true && left == false)
	{
		SetWindowPos(hWnd, HWND_TOP, posX, posY += 5, 300, 300, SWP_SHOWWINDOW);
		if (rhWnd.bottom >= Vertres - (rShellTray.bottom - rShellTray.top))
			up = false;
	}

	else if (up == false && left == false)
	{
		SetWindowPos(hWnd, HWND_TOP, posX -= 5, posY, 300, 300, SWP_SHOWWINDOW);
		if (rhWnd.left == 0)
			left = true;
	}

	else if (up == false && left == true)
	{
		SetWindowPos(hWnd, HWND_TOP, posX, posY -= 5, 300, 300, SWP_SHOWWINDOW);
		if (rhWnd.top == 0)
			up = true;
	}
}


//LMB - opens calculator
//RMB - initializes calculator buttons 
//s - minimizes calculator buttons in a row
//d - restore calculator buttons in a row
//enter - start to move window
//esc - stop to move window



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	case WM_KEYDOWN:
	{
		if (wParam == VK_RETURN)
		{
			SetWindowPos(hWnd, HWND_TOP, 0, 0, 300, 300, SWP_SHOWWINDOW);
			SetTimer(hWnd, 1, 1, TimerProc);
		}

		else if (wParam == VK_ESCAPE)
		{
			KillTimer(hWnd, 1);
		}
		break;

	case WM_LBUTTONDOWN:
		WinExec("C:\\Windows\\system32\\calc.exe", SW_SHOWNORMAL);
		break;
	case WM_RBUTTONDOWN:
		Calc = FindWindow(_TEXT("CalcFrame"), _TEXT("Калькулятор"));
		EnumChildWindows(Calc, EnumChildProc, NULL);
		counter = 0;
		break;

	case WM_CHAR:
		if (wParam == _TEXT('s'))
		{
			if (counter < 100)
				minimize(Calc);
		}

		else if (wParam == _TEXT('d'))

		{
			if (counter > 0)
				maximize(Calc);
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


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	TCHAR str[64] = { 0 };
	GetClassName(hWnd, str, 64);
	if (!_tcscmp(str, _TEXT("Button")))
		buttons[counter++] = hWnd;
	return TRUE;
}



void minimize(HWND hwnd)
{
	if (buttons[counter])
		ShowWindow(buttons[counter++], SW_MINIMIZE);
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
}

void maximize(HWND hwnd)
{
	if (buttons[--counter])
		ShowWindow(buttons[counter], SW_RESTORE);
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
	InvalidateRect(hwnd, NULL, TRUE);
}
