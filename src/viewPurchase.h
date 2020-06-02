#include <windows.h>
#include "resources.h"
#include "util.h"
#include "database.h"

LRESULT CALLBACK PurchaseWndProc(HWND mainWindow, HWND midClient, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			int posY = 50;
			
			AddLabel(hwnd, ID_FORM_COM_INFO, "COMPROVANTE DA COMPRA.", 50, posY, 400, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_1, "Cliente:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_2, tickets[ticketsCount - 1].ClientName, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_3, "Peça:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_4, tickets[ticketsCount - 1].Place, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_3, "Assento:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_4, tickets[ticketsCount - 1].TheaterName, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_5, "Dia:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_6, tickets[ticketsCount - 1].Date, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_7, "Hr. Inicial:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_8, tickets[ticketsCount - 1].Start, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_9, "Hr. Final:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_10, tickets[ticketsCount - 1].End, 150, posY, 200, 20);
			posY += 50;
			
			char vl[5];
			snprintf(vl, sizeof vl, "%f", tickets[ticketsCount - 1].OriginalValue);
		
			AddLabel(hwnd, ID_FORM_COM_LB_11, "Valor Original:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_12, vl, 150, posY, 200, 20);
			posY += 50;
			
			AddLabel(hwnd, ID_FORM_COM_LB_13, "Desconto:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_14, tickets[ticketsCount - 1].Discount, 150, posY, 200, 20);
			posY += 50;
			
			snprintf(vl, sizeof vl, "%f", tickets[ticketsCount - 1].Value);
		
			AddLabel(hwnd, ID_FORM_COM_LB_15, "Valor Pago:", 50, posY, 100, 20);
			AddLabel(hwnd, ID_FORM_COM_LB_16, vl, 150, posY, 200, 20);
			
			break;
		}
		
		case WM_MDIACTIVATE: {
			HMENU hMenu, hSubMenu;
			
			hMenu = GetMenu(mainWindow);
			hSubMenu = GetSubMenu(hMenu, 0);
			
			EnableMenuItem(hSubMenu, ID_MENU_SALES, MF_ENABLED);
			EnableMenuItem(hSubMenu, ID_MENU_BOX, MF_ENABLED);
			
			DrawMenuBar(mainWindow);
			
			HWND hStatus = GetDlgItem(mainWindow, ID_MAIN_STATUS);
						
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Recibo de compra carregado com sucesso.");
			
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
