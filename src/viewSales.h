#include <windows.h>
#include "resources.h"
#include "crossCutting.h"

LRESULT CALLBACK SalesWndProc(HWND mainWindow, int menuActive, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int t[] = { 1, 2, 3 };
	
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
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_4, "Selecione a atra��o:", 50, 200, 150, 20);
			
			Columns cols[1];
			
			strcpy(cols[0].Name, "Pe�a");
			cols[0].Width = 100;
			
			strcpy(cols[1].Name, "Valor");
			cols[1].Width = 100;
			
			AddListView(hwnd, ID_FORM_VENDA_LV_1, 250, 200, 300, 100, cols);
			
			CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_2, -1);
			
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
		case WM_NOTIFY: {
			HWND hListView = GetDlgItem(hwnd, ID_FORM_VENDA_LV_1);
			NMHDR* header = (NMHDR*)lParam;
	        NMLISTVIEW* nmlist = (NMLISTVIEW*)lParam;
	        
	        if (header->hwndFrom == hListView && header->code == LVN_ITEMCHANGED)
	        {
	            if (nmlist->uNewState & LVIS_SELECTED)
				{
					MessageBox(hwnd, "Selecionado", "", MB_OK);
	            }
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
