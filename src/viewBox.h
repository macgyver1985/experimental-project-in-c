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
			
			Columns cols[5];
			
			strcpy(cols[0].Name, "Cliente");
			cols[0].Width = 100;
			
			strcpy(cols[1].Name, "Peça");
			cols[1].Width = 100;
			
			strcpy(cols[2].Name, "Valor Original");
			cols[2].Width = 100;
			
			strcpy(cols[3].Name, "% Desconto");
			cols[3].Width = 100;
			
			strcpy(cols[4].Name, "Valor Pago");
			cols[4].Width = 100;
			
			DisplayTicketsInListView(
				AddListView(hwnd, ID_FORM_BOX_LV_1, 50, posY, 600, 400, cols, 5),
				tickets,
				120
			);
			posY += 430;
			
			AddLabel(hwnd, ID_FORM_BOX_LB_1, "VALOR TOTAL:", 50, posY, 100, 20);
			
			float vlt;
			int i;
			
			for(i = 0; i < 120; i += 1) {
				if(tickets[i].IsSold == FALSE) {
					break;
				}
				
				vlt += tickets[i].Value;
			}
			
			char vl[7];
			snprintf(vl, sizeof vl, "%f", vlt);
			
			AddLabel(hwnd, ID_FORM_BOX_LB_2, vl, 160, posY, 100, 20);
			
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
