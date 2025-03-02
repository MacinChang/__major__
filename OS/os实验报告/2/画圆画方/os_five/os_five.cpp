// os_five.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "os_five.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
HWND g_hWnd;
HDC g_hdc;
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];	// 主窗口类名
struct Node{
	HWND hWnd;
	HDC hdc;
};

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OS_FIVE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OS_FIVE));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OS_FIVE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OS_FIVE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

DWORD WINAPI ThreadProcSquare(LPVOID pParam){
	HWND hWnd = g_hWnd;
	HDC hdc = g_hdc;;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	SetDCBrushColor(hdc, BLACK);
	hBrush = GetStockBrush(DC_BRUSH);
	SelectObject(hdc, hBrush);
	int x, y;
	//顺时针方向描点画矩形
	for (x = 160; x < 340; x++){
		SetPixel(hdc, x, 160, BLACK);
		Sleep(50);
	}
	for (y = 160; y < 340; y++){
		SetPixel(hdc, 340, y, BLACK);
		Sleep(50);
	}
	for (x = 340; x > 160; x--){
		SetPixel(hdc, x, 340, BLACK);
		Sleep(50);
	}
	for (y = 340; y > 160; y--){
		SetPixel(hdc, 160, y, BLACK);
		Sleep(50);
	}
	DeleteObject(hBrush);
	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, hdc);
	return 0;
}

DWORD WINAPI ThreadProcCircle(LPVOID pParam){
 	HWND hWnd = g_hWnd;
	HDC hdc = g_hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	SetDCBrushColor(hdc, BLACK);
	hBrush = GetStockBrush(DC_BRUSH);
	SelectObject(hdc, hBrush);
	struct LOC{
		int x, y;
	}M, N;
	const double pi = 3.14159265358979;
	M.x = 750;
	M.y = 250;
	//以(M.x,M.y)为圆心，以R为半径，描点画圆
	//共描720个点，隔0.5度(STEP)描一次
	double angle = -pi, R = 160, STEP = (pi * 0.5) / 180;
	while (angle - 180 < 1e10){
		N.x = M.x + R * sin(angle);
		N.y = M.y + R * cos(angle);
		angle += STEP;
		SetPixel(hdc, N.x, N.y, BLACK);
		Sleep(50);
	}
	DeleteObject(hBrush);
	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, hdc);
	return 0;
}
//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		g_hdc = BeginPaint(hWnd, &ps);
		g_hWnd = hWnd;
		HANDLE h[2];
		DWORD threadIdSquare, threadIdCircle;
		//生成两个线程
		h[0] = CreateThread(NULL, 0, ThreadProcSquare, NULL, 0, &threadIdSquare);
		h[1] = CreateThread(NULL, 0, ThreadProcCircle, NULL, 0, &threadIdCircle);
		WaitForMultipleObjects(2, h, TRUE, INFINITE);
		break;
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
