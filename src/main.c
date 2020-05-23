#include <windows.h>
#include <commctrl.h>
#include "resources.h"

const char g_szClassName[] = "myWindowClass";
const char g_szChildClassName[] = "myMDIChildWindowClass";
HWND g_hMDIClient = NULL;
HWND g_hMainWindow = NULL;

HWND CreateNewMDIChild(HWND hMDIClient, LPCWSTR title)
{
	MDICREATESTRUCT mcs;
	HWND hChild;

	mcs.szTitle = title;
	mcs.szClass = g_szChildClassName;
	mcs.hOwner  = GetModuleHandle(NULL);
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;
	
	hChild = (HWND)SendMessage(hMDIClient, WM_MDICREATE, 0, (LONG)&mcs);
	
	ShowWindow(hChild, SW_MAXIMIZE);
	UpdateWindow(hChild);
	
	if(!hChild)
	{
		MessageBox(hMDIClient, "MDI Child creation failed.", "Oh Oh...",
			MB_ICONEXCLAMATION | MB_OK);
	}
	
	return hChild;
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		// Aqui são aplicadas as configuração iniciais da janela no momento da sua criação.
		case WM_CREATE:{
			// Constroe e vincula os menus à janela principal.
			HMENU hMenu, hSubMenuOne;
			
			hMenu = CreateMenu();
			hSubMenuOne = CreatePopupMenu();
			
			AppendMenu(hSubMenuOne, MF_STRING, ID_MENU_10, "V&ender");
			//AppendMenu(hSubMenuOne, MF_SEPARATOR, -1, "");
			AppendMenu(hSubMenuOne, MF_STRING, ID_MENU_11, "C&aixa");
			//AppendMenu(hSubMenuOne, MF_SEPARATOR, -1, "");
			AppendMenu(hSubMenuOne, MF_STRING, ID_MENU_12, "S&air");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenuOne, "I&niciar");
			
			SetMenu(hwnd, hMenu);
			
			CLIENTCREATESTRUCT ccs;
			
		    ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 1);
		    ccs.idFirstChild = ID_MDI_SALE;
			
		    g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
		        WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
		        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		        hwnd, (HMENU)ID_MENU_10, GetModuleHandle(NULL), (LPVOID)&ccs);
		    
		  	if(g_hMDIClient == NULL)
				MessageBox(hwnd, "Could not create MDI client.", "Error", MB_OK | MB_ICONERROR);
			
			break;
		}
		
		// Trata as ações do menu do sistema
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_MENU_10:
					CreateNewMDIChild(g_hMDIClient, "Venda");
					break;
				
				case ID_MENU_11:
					
					break;
				
				case ID_MENU_12:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				
			}
			
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			//return DefWindowProc(hwnd, Message, wParam, lParam);
			return DefFrameProc(hwnd, g_hMDIClient, Message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			break;
		}
		
		case WM_MDIACTIVATE: {
			break;
		}
		
		case WM_COMMAND: {
			break;
		}
		case WM_SIZE:{
			break;
		}
		default:
			return DefMDIChildProc(hwnd, msg, wParam, lParam);
	
	}
	return 0;
}

BOOL SetUpMDIChildWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	 = MDIChildWndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = g_szChildClassName;
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(0, "Could Not Register Child Window", "Oh Oh...", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}
	else
		return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	
	memset(&wc,0,sizeof(wc));
	
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = g_szClassName;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	if(!SetUpMDIChildWindowClass(hInstance))
		return 0;

	hwnd = CreateWindowEx(
		0,
		g_szClassName,
		"Sistema de Venda de Ingresssos",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	g_hMainWindow = hwnd;
	
	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		if (!TranslateMDISysAccel(g_hMDIClient, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}
