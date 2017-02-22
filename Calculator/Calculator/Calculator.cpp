#define _USE_MATH_DEFINES
#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <cmath>
#include "resource.h"


INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
static HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_CALCULATOR), NULL, DlgProc);
}


INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HWND hScreen1, hScreen2, hRange;
	static TCHAR screen1[128] = { 0 };
	static TCHAR screen2[128] = { 0 };
	static double result = 0;
	static bool clicked = false;
	static char action = 0;
	static int index = 0;
	static int range = 2;

	switch (message)
	{
	case WM_INITDIALOG:
	{
						  HANDLE hIco = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
						  SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIco);
						  SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIco);
						  hScreen1 = GetDlgItem(hWnd, IDC_SCREEN1);
						  hScreen2 = GetDlgItem(hWnd, IDC_SCREEN2);
						  hRange = GetDlgItem(hWnd, IDC_RANGE);
						  index = SendMessage(hRange, CB_ADDSTRING, 0, LPARAM(TEXT("0")));
						  SendMessage(hRange, CB_SETITEMDATA, index, 0);
						  index = SendMessage(hRange, CB_ADDSTRING, 0, LPARAM(TEXT("1")));
						  SendMessage(hRange, CB_SETITEMDATA, index, 1);
						  index = SendMessage(hRange, CB_ADDSTRING, 0, LPARAM(TEXT("2")));
						  SendMessage(hRange, CB_SETITEMDATA, index, 2);
						  index = SendMessage(hRange, CB_ADDSTRING, 0, LPARAM(TEXT("3")));
						  SendMessage(hRange, CB_SETITEMDATA, index, 3);
						  index = SendMessage(hRange, CB_ADDSTRING, 0, LPARAM(TEXT("4")));
						  SendMessage(hRange, CB_SETITEMDATA, index, 4);

	}
		return TRUE;

	case WM_COMMAND:
	{
					   if (LOWORD(wParam) == IDC_RANGE && HIWORD(wParam) == CBN_SELCHANGE)
					   {
						   index = SendMessage(hRange, CB_GETCURSEL, 0, 0);
						   range = SendMessage(hRange, CB_GETITEMDATA, index, 0);
						   GetWindowText(hScreen2, screen2, 128);
						   double temp_screen2 = _tcstod(screen2, TEXT('\0'));
						   _stprintf_s(screen2, TEXT("%.*f"), range, temp_screen2);
						   SendMessage(hScreen2, WM_SETTEXT, 0, LPARAM(screen2));
					   }
					   					
					   if ((LOWORD(wParam) == IDC_B1) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("1"));
						   SetWindowText(hScreen1, screen1);
					   }

					   if ((LOWORD(wParam) == IDC_B2) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("2"));
						   SetWindowText(hScreen1, screen1);
					   }

					   if ((LOWORD(wParam) == IDC_B3) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("3"));
						   SetWindowText(hScreen1, screen1);
					   }

					   if ((LOWORD(wParam) == IDC_B4) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("4"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_B5) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("5"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_B6) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("6"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_B7) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("7"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_B8) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("8"));
						   SetWindowText(hScreen1, screen1);

					   }
					   if ((LOWORD(wParam) == IDC_B9) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscat_s(screen1, TEXT("9"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_B0) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] == '\0')
							   _tcscat_s(screen1, TEXT("0."));
						   else
							   _tcscat_s(screen1, TEXT("0"));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_BSPOT) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] == '\0')
							   _tcscat_s(screen1, TEXT("0."));
						   else
							   _tcscat_s(screen1, TEXT("."));
						   SetWindowText(hScreen1, screen1);
					   }
					   if ((LOWORD(wParam) == IDC_BPI) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _stprintf_s(screen1, TEXT("%f"), M_PI);
						   SetWindowText(hScreen1, screen1);
					   }

					   if ((LOWORD(wParam) == IDC_BBACKSPACE) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] == '\0') return TRUE;
						   int i = 0;
						   while (screen1[i] != '\0')
						   {
							   ++i;
						   }
						   screen1[i - 1] = '\0';
						   SetWindowText(hScreen1, screen1);
					   }

					   if ((LOWORD(wParam) == IDC_BC) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   _tcscpy_s(screen1, TEXT("\0"));
						   _tcscpy_s(screen2, TEXT("\0"));
						   SetWindowText(hScreen1, TEXT("\0"));
						   SetWindowText(hScreen2, TEXT("\0"));
						   result = 0;
						   clicked = false;
					   }

					   if ((LOWORD(wParam) == IDC_BRETURN) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if ((result != 0) && (screen1[0] != NULL))
						   {
							   switch (action)
							   {
							   case '+': result += _tcstod(screen1, TEXT('\0')); break;
							   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
							   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
							   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
							   default: break;
							   }
							   _stprintf_s(screen2, TEXT("%.*f"),range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   _tcscpy_s(screen2, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   clicked = false;
						   }
					   }

					   if ((LOWORD(wParam) == IDC_BPERCENT) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if ((screen1[0] != '\0') && (result != 0))
						   {
							   double temp_screen1 = result * (_tcstod(screen1, TEXT('\0')) / 100);
							   _stprintf_s(screen1, TEXT("%.*f"), range, temp_screen1);
							   SetWindowText(hScreen1, screen1);
						   }
						   else return TRUE;
					   }

					   if ((LOWORD(wParam) == IDC_BREVERSE) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] != '\0')
						   {
							   if (result != 0)
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   result = 1 / result;
							   }
							   else result = 1 / _tcstod(screen1, TEXT('\0'));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   result = 0;
							   clicked = false;
						   }
						   else if (screen2[0] != '\0')
						   {
							   result = 1 / _tcstod(screen2, TEXT('\0'));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   result = 0;
							   clicked = false;
						   }
						   else return TRUE;
					   }

					   if ((LOWORD(wParam) == IDC_BSQRT) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] != '\0')
						   {
							   if (result < 0)
							   {
								   SetWindowText(hScreen2, TEXT("Impossible operation."));
								   return TRUE;
							   }
							   else if (result > 0)
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   if (result < 0)
								   {
									   SetWindowText(hScreen2, TEXT("Impossible operation."));
									   return TRUE;
								   }
								   else result = sqrt(result);
							   }
							   else if (result == 0)
							   {
								   if (_tcstod(screen1, TEXT('\0')) < 0)
								   {
									   SetWindowText(hScreen2, TEXT("Impossible operation."));
									   return TRUE;
								   }
								   else if (_tcstod(screen1, TEXT('\0')) >= 0)
									   result = sqrt(_tcstod(screen1, TEXT('\0')));
							   }
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   result = 0;
							   clicked = false;
						   }
						   else return TRUE;
					   }

					   if ((LOWORD(wParam) == IDC_BSQUARE) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] != '\0')
						   {
							   if (result != 0)
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   result *= result;
							   }
							   else
							   {
								   result = _tcstod(screen1, TEXT('\0'));
								   result *= result;
							   }
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   result = 0;
							   clicked = false;
						   }
						   else if (screen2[0] != '\0')
						   {
							   result = _tcstod(screen2, TEXT('\0'));
							   result *= result;
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   result = 0;
							   clicked = false;
						   }
						   else return TRUE;
					   }


					   if ((LOWORD(wParam) == IDC_BSIN) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] != '\0')
						   {
							   if (result != 0)
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   result = sin(result);
							   }
							   else result = sin(_tcstod(screen1, TEXT('\0')));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   _tcscpy_s(screen2, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   result = 0;
							   clicked = false;
						   }
						   else if (screen2[0] != '\0')
						   {
							   result = sin(_tcstod(screen2, TEXT('\0')));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   result = 0;
							   clicked = false;
						   }
						   else return TRUE;
					   }

					   if ((LOWORD(wParam) == IDC_BCOS) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (screen1[0] != '\0')
						   {
							   if (result != 0)
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   result = cos(result);
							   }
							   else result = cos(_tcstod(screen1, TEXT('\0')));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   _tcscpy_s(screen1, TEXT("\0"));
							   _tcscpy_s(screen2, TEXT("\0"));
							   SetWindowText(hScreen1, screen1);
							   result = 0;
							   clicked = false;
						   }
						   else if (screen2[0] != '\0')
						   {
							   result = cos(_tcstod(screen2, TEXT('\0')));
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   SetWindowText(hScreen2, screen2);
							   result = 0;
							   clicked = false;
						   }
						   else return TRUE;
					   }

					   if ((LOWORD(wParam) == IDC_BPLUS) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (!clicked)
						   {
							   if (screen1[0] == '\0') return TRUE;
							   result = _tcstod(screen1, TEXT('\0'));
							   _tcscpy_s(screen2, screen1);
							   _tcscat_s(screen2, TEXT(" + "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   action = '+';
							   clicked = true;
						   }
						   else
						   {
							   if (screen1[0] == '\0') return TRUE;
							   switch (action)
							   {
							   case '+': result += _tcstod(screen1, TEXT('\0')); break;
							   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
							   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
							   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
							   default: break;
							   }
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   _tcscat_s(screen2, TEXT(" + "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   action = '+';
						   }
					   }


					   if ((LOWORD(wParam) == IDC_BMINUS) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (!clicked)
						   {
							   if (screen1[0] == '\0')
							   {
								   _tcscat_s(screen1, TEXT("-"));
								   SetWindowText(hScreen1, screen1);
							   }
							   else
							   {
								   result = _tcstod(screen1, TEXT('\0'));
								   _tcscpy_s(screen2, screen1);
								   _tcscat_s(screen2, TEXT(" - "));
								   _tcscpy_s(screen1, TEXT("\0"));
								   SetWindowText(hScreen2, screen2);
								   SetWindowText(hScreen1, TEXT("\0"));
								   clicked = true;
								   action = '-';
							   }
						   }
						   else
						   {
							   if (screen1[0] == '\0')
							   {
								   _tcscat_s(screen1, TEXT("-"));
								   SetWindowText(hScreen1, screen1);
							   }
							   else
							   {
								   switch (action)
								   {
								   case '+': result += _tcstod(screen1, TEXT('\0')); break;
								   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
								   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
								   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
								   default: break;
								   }
								   _stprintf_s(screen2, TEXT("%.*f"), range, result);
								   _tcscat_s(screen2, TEXT(" - "));
								   _tcscpy_s(screen1, TEXT("\0"));
								   SetWindowText(hScreen2, screen2);
								   SetWindowText(hScreen1, TEXT("\0"));
								   action = '-';
							   }
						   }
					   }

					   if ((LOWORD(wParam) == IDC_BMULTIPLY) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (!clicked)
						   {
							   if (screen1[0] == '\0') return TRUE;
							   result = _tcstod(screen1, TEXT('\0'));
							   _tcscpy_s(screen2, screen1);
							   _tcscat_s(screen2, TEXT(" * "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   clicked = true;
							   action = '*';
						   }
						   else
						   {
							   if (screen1[0] == '\0') return TRUE;
							   switch (action)
							   {
							   case '+': result += _tcstod(screen1, TEXT('\0')); break;
							   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
							   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
							   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
							   default: break;
							   }
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   _tcscat_s(screen2, TEXT(" * "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   action = '*';
						   }
					   }

					   if ((LOWORD(wParam) == IDC_BDEVIDE) && (HIWORD(wParam) == BN_CLICKED))
					   {
						   if (!clicked)
						   {
							   if (screen1[0] == '\0') return TRUE;
							   result = _tcstod(screen1, TEXT('\0'));
							   _tcscpy_s(screen2, screen1);
							   _tcscat_s(screen2, TEXT(" / "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   clicked = true;
							   action = '/';
						   }
						   else
						   {
							   if (screen1[0] == '\0') return TRUE;
							   switch (action)
							   {
							   case '+': result += _tcstod(screen1, TEXT('\0')); break;
							   case '-': result -= _tcstod(screen1, TEXT('\0')); break;
							   case '*': result *= _tcstod(screen1, TEXT('\0')); break;
							   case '/': result /= _tcstod(screen1, TEXT('\0')); break;
							   default: break;
							   }
							   _stprintf_s(screen2, TEXT("%.*f"), range, result);
							   _tcscat_s(screen2, TEXT(" / "));
							   _tcscpy_s(screen1, TEXT("\0"));
							   SetWindowText(hScreen2, screen2);
							   SetWindowText(hScreen1, TEXT("\0"));
							   action = '/';
						   }
					   }

					   return TRUE;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
