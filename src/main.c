#include <windows.h>
#include <commctrl.h>
#include "resources.h"

const char g_szClassName[] = "myWindowClass";
const char g_szChildClassName[] = "myMDIChildWindowClass";
HWND g_hMainWindow = NULL;
HWND g_hMDIClient = NULL;
HWND currentMDIChild = NULL;
HWND hStatus = NULL;

HWND CreateNewMDIChild(HWND hMDIClient, LPCWSTR title)
{
	if(currentMDIChild != NULL)
		DestroyWindow(currentMDIChild);
	
	MDICREATESTRUCT mcs;

	mcs.szTitle = title;
	mcs.szClass = g_szChildClassName;
	mcs.hOwner  = GetModuleHandle(NULL);
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;
	
	currentMDIChild = (HWND)SendMessage(hMDIClient, WM_MDICREATE, 0, (LONG)&mcs);
	
	ShowWindow(currentMDIChild, SW_MAXIMIZE);
	UpdateWindow(currentMDIChild);
	
	if(!currentMDIChild)
		MessageBox(hMDIClient, "MDI Child creation failed.", "Oh Oh...", MB_ICONEXCLAMATION | MB_OK);
		
	return currentMDIChild;
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		// Aqui são aplicadas as configuração iniciais da janela no momento da sua criação.
		case WM_CREATE:{
			/*
				# Constroe e vincula o frame que vai receber as MDIChilds #
			*/
			CLIENTCREATESTRUCT ccs;
			
		    ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 1);
		    ccs.idFirstChild = ID_MDI_FIRSTCHILD;
			
		    g_hMDIClient = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				"mdiclient",
				NULL,
		        WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
		        CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
		        hwnd,
				(HMENU)ID_MAIN_MDI,
				GetModuleHandle(NULL),
				(LPVOID)&ccs);
		    
		  	if(g_hMDIClient == NULL)
				MessageBox(hwnd, "Could not create MDI client.", "Error", MB_OK | MB_ICONERROR);
			
			/*
				# Constroe e vincula a barra de status na janela principal #
			*/
			int statwidths[] = {100, -1};
			hStatus = CreateWindowEx(
				0,
				STATUSCLASSNAME,
				NULL,
				WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
				0, 0, 0, 0,
				hwnd,
				(HMENU)ID_MAIN_STATUS,
				GetModuleHandle(NULL),
				NULL);

			SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths)/sizeof(int), (LPARAM)statwidths);
			SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)"Hi there :)");
			
			break;
		}
		
		// Trata as ações que são executadas pelos menus do sistema.
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_MENU_SALES:
					CreateNewMDIChild(g_hMDIClient, "Venda");
					break;
				
				case ID_MENU_BOX:
					CreateNewMDIChild(g_hMDIClient, "Caixa");
					break;
				
				case ID_MENU_CLOSE:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
			}
			break;
		
		// Ajusta a posição dos componentes de acordo com o tamanho da janela.
		case WM_SIZE:{
			/*
				# Ajusta a posição do status bar #
			*/
			RECT rcStatus;
			HWND hStatus = GetDlgItem(hwnd, ID_MAIN_STATUS);
			SendMessage(hStatus, WM_SIZE, 0, 0);
			
			GetWindowRect(hStatus, &rcStatus);
			int iStatusHeight = rcStatus.bottom - rcStatus.top;
			
			/*
				#  #
			*/
			RECT rcClient;
			GetClientRect(hwnd, &rcClient);
			int iMDIHeight = rcClient.bottom - iStatusHeight;
			HWND hMDI = GetDlgItem(hwnd, ID_MAIN_MDI);
			
			SetWindowPos(hMDI, NULL, 0, 0, rcClient.right, iMDIHeight, SWP_NOZORDER);
			
			break;
		}
			
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			
		default:
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
	wc.lpszMenuName  = MAKEINTRESOURCE(ID_MENU_ROOT);
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
		"Sistema de Venda de Ingressos",
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
