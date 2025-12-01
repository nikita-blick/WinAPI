//MainWindow
#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) регистраци€ класса окна. Ќа этом этапе класс нашего окна регистрируетс€ в ќ—.
	//	 класс окна это не тип данных, как в ќќѕ, класс любого окна представл€ет собой 
	//	 самую обычную строку с именем класса.
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	// инициализируем размеры и стиль:
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);	//cb_ - Count Bytes
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	// инициализируем внешний вид окон:
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_EURO));
	//wClass.hIcon = (HICON)LoadImage(NULL, "euro.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(NULL, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"starcraft-original\\Link Select.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// инициализаци€ системных переменных:
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyle
		g_sz_WINDOW_CLASS,	// им€ класса окна
		g_sz_WINDOW_CLASS,	// заголовок окна
		WS_OVERLAPPEDWINDOW,// стиль окна. —тили всегда завис€т от класса окна. 'WS_OVERLAPPEDWINDOW' - нлавное окно
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position
		640, 480,	// размер окна
		NULL,
		NULL,	// дл€ главного окна это ResourceID главного меню, 
		// дл€ дочернего окна (Control) - ResourceID дочернего окна (IDC_BUTTON_COPY)
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	// задает режим отображени€ окна - –азвернуто на весь экран, —вернуто в окно, —вернуто на панель задач.
	UpdateWindow(hwnd);	// обновл€ет рабочую область окна отправл€€ сообщение 'WM_PAINT', 
	// если клиентска€ область окна не пуста€.

//3) запуск цикла сообщений:
	MSG msg;	//
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);	// преобразует сообщени€ виртуальных клавиш в символьные сообщени€.
		DispatchMessage(&msg);	// отправл€ет сообщение в процедуру окна.
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, "Cursor check", "Info", MB_OK | MB_ICONINFORMATION);
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}