#include <windows.h>
#include "resources.h"
#include "util.h"
#include "database.h"

LRESULT CALLBACK BoxWndProc(HWND mainWindow, HWND midClient, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			int posY = 50;
			
			AddLabel(hwnd, ID_FORM_BOX_INFO, "FLUXO DE CAIXA", 50, posY, 400, 20);
			posY += 50;
			
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
			
			HWND hStatus = GetDlgItem(mainWindow, ID_MAIN_STATUS);
						
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Fluxo de caixa carregado com sucesso.");
			
			break;
		}
		
		case WM_COMMAND: {
			
			
			break;
		}
		
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			
			break;
		}
			
		default:
			return DefMDIChildProc(hwnd, msg, wParam, lParam);
	}
	
	return 0;
}
