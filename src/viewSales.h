#include <windows.h>
#include "resources.h"

LRESULT CALLBACK SalesWndProc(HWND mainWindow, int menuActive, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			 HWND hwndEdit = CreateWindowEx(
			 	WS_EX_WINDOWEDGE,
				"static",
				"teste: ",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				0, 0, 100, 100,
				hwnd,
				(HMENU)ID_FORM_VENDA_INFO,
				GetModuleHandle(NULL),
				NULL);
				
				if(hwndEdit == NULL)
					MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
			
			break;
		}
		
		case WM_MDIACTIVATE: {
			HMENU hMenu, hSubMenu;
			
			hMenu = GetMenu(mainWindow);
			hSubMenu = GetSubMenu(hMenu, 0);
			
			EnableMenuItem(hSubMenu, ID_MENU_SALES, MF_ENABLED);
			EnableMenuItem(hSubMenu, ID_MENU_BOX, MF_ENABLED);
			EnableMenuItem(hSubMenu, menuActive, MF_GRAYED);
			
			DrawMenuBar(mainWindow);
			
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
