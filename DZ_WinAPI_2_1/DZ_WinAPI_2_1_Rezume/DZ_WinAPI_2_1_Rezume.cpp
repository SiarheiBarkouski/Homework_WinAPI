#include<windows.h>
#include<tchar.h>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	TCHAR szTitleFirst[] = _TEXT("Резюме!");
	TCHAR szName[] = _TEXT("Меня зовут Сергей.");
	TCHAR szSurname[] = _TEXT("Мне 23 года.");
	TCHAR szEndName[] = _TEXT("Я учусь в ITSTEP.");
	MessageBox(NULL, szName, szTitleFirst, MB_OK);
	MessageBox(NULL, szSurname, szTitleFirst, MB_OK);
	TCHAR szTitleEnd[100];
	int count = ((_tcslen(szName) + _tcslen(szSurname) + _tcslen(szEndName)) / 3);
	_stprintf(szTitleEnd, _TEXT("Среднее число символов: %i"), count);
	MessageBox(NULL, szEndName, szTitleEnd, MB_OK);
	return 0;
}