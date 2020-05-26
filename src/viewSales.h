#include <windows.h>
#include "resources.h"
#include "crossCutting.h"

const char eventos[9][30] = {
    "Mercury", "Venus", "Terra", "Mars",
    "Jupiter", "Saturn", "Uranus", "Neptune",
    "Pluto??"
};

LRESULT CALLBACK SalesWndProc(HWND mainWindow, int menuActive, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			AddLabel(hwnd, ID_FORM_VENDA_INFO, "Informe os dados do cliente e selecione o evento.", 50, 50, 400, 20);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_1, "Nome do Cliente: ", 50, 100, 120, 20);
			AddTextBox(hwnd, ID_FORM_VENDA_TXT_1, NULL, 170, 100, 280, 20, 30);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_2, "Idade: ", 480, 100, 50, 20);
			AddTextBox(hwnd, ID_FORM_VENDA_TXT_2, NULL, 530, 100, 40, 20, 2);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_3, "Meia entrada para:", 50, 150, 130, 20);
			AddRadioButton(hwnd, ID_FORM_VENDA_RAD_1, "Estudante", 190, 150, 100, 20);
			AddRadioButton(hwnd, ID_FORM_VENDA_RAD_2, "Professor", 290, 150, 100, 20);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_4, "Selecione a atração:", 50, 200, 150, 20);
			AddComboBox(hwnd, ID_FORM_VENDA_CB_1, 250, 200, 300, 100, eventos);
			
			CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_2, NULL);
			
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
			switch(LOWORD(wParam)) {
				case ID_FORM_VENDA_RAD_1:
					CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_2, ID_FORM_VENDA_RAD_1);
					break;
				case ID_FORM_VENDA_RAD_2:
					CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_2, ID_FORM_VENDA_RAD_2);
					break;
			}
			
			break;
		}
		case WM_KEYDOWN: {
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
