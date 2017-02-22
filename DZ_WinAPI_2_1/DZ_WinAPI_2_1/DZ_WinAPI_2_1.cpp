#include <windows.h>
#include <tchar.h>
#include <string>

#define  APPNAME    TEXT("Guess the number")
#define  APPCLS     TEXT("win32app")
#define  IDC_SMALL  100
#define  IDC_BIG    101
#define  IDC_ANSWER 102

LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
void  begin(HWND);
void  guess(HWND, char);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	HWND hwnd = NULL;
	MSG  msg = { 0 };

	WNDCLASS wnex = 
	{
		0, WndProc, 0, 0, hInstance, 0, LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1), 0, APPCLS
	};
	if (!RegisterClass(&wnex))
		return 1;

	hwnd = CreateWindow(APPCLS, TEXT("Guess the number!"), WS_OVERLAPPEDWINDOW,
		200, 200, 400, 300, HWND_DESKTOP,
		NULL, hInstance, hInstance);

	if (hwnd == NULL)
	{
		UnregisterClass(APPCLS, hInstance);
		return TRUE;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	HWND bigger = NULL;
	HWND smaller = NULL;
	RECT  rc;

	switch (msg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rc);
		smaller = CreateWindow(TEXT("BUTTON"), TEXT("Smaller"), WS_CHILD | BS_USERBUTTON | WS_VISIBLE,
			rc.left + 80, rc.bottom / 2 - 20, 90, 35, hwnd, (HMENU)IDC_SMALL, (HINSTANCE)lParam, NULL);
		bigger = CreateWindow(TEXT("BUTTON"), TEXT("Bigger"), WS_CHILD | BS_USERBUTTON | WS_VISIBLE,
			rc.right - 170, rc.bottom / 2 - 20, 90, 35, hwnd, (HMENU)IDC_BIG, (HINSTANCE)lParam, NULL);
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_ANSWER, 0), 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDC_SMALL:
			guess(hwnd,'<');
			break;
		case IDC_BIG:
			guess(hwnd,'>');
			break;
		case IDC_ANSWER:
			begin(hwnd);
			guess(hwnd, 0);
			break;
		}
		break;

	case WM_DESTROY:
		DestroyWindow(smaller);
		DestroyWindow(bigger);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


void  begin(HWND hwnd) 
{
	MessageBox(hwnd, TEXT("Choose a number between 1 and 100"), APPNAME, MB_OK | MB_ICONINFORMATION);
}


void  guess(HWND hwnd, char ch) 
{
	static int first = 1;
	static int last = 100;
	static int result = 0;
	static int counter = 0;
	int id;
	TCHAR str[64];
	
	switch (ch) 
	{
	case '<': 
		last = result;
		break;
	case '>': 
		first = result + 1;
		break;
	}

	counter++;
	result = (first + last) / 2;
	

	wsprintf(str, TEXT("You chose %d. Yes or No?"), result);
	id = MessageBox(hwnd, str, APPNAME, MB_YESNO | MB_ICONQUESTION);
	if (id != IDYES)
		return;

	wsprintf(str, TEXT("I guessed the number in %d attempts.\nDo you want to continue?"), counter);
	id = MessageBox(hwnd, str, APPNAME, MB_YESNO | MB_ICONINFORMATION);
	if (id == IDNO) 
		SendMessage(hwnd, WM_DESTROY, 0, 0);
	else 
	{  
		first = 1;
		last = 100;
		counter = result = 0;
		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_ANSWER, 0), 0);
	}
}