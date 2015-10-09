// os_five.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "os_five.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
HWND g_hWnd;
HDC g_hdc;
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];	// ����������
struct Node{
	HWND hWnd;
	HDC hdc;
};

// �˴���ģ���а����ĺ�����ǰ������: 
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

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OS_FIVE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OS_FIVE));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
	//˳ʱ�뷽����㻭����
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
	//��(M.x,M.y)ΪԲ�ģ���RΪ�뾶����㻭Բ
	//����720���㣬��0.5��(STEP)��һ��
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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		//���������߳�
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

// �����ڡ������Ϣ�������
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
