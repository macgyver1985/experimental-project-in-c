#include <windows.h>
#include "resources.h"
#include "util.h"
#include "database.h"

char* clientName;
char* year;
char* place;
int halfEntry = 0;
int showSelected = -1;

LRESULT CALLBACK SalesWndProc(HWND mainWindow, HWND midClient, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: {
			halfEntry = 0;
			showSelected = -1;
			
			AddLabel(hwnd, ID_FORM_VENDA_INFO, "Informe os dados do cliente e selecione o evento.", 50, 50, 400, 20);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_1, "Nome do Cliente: ", 50, 100, 120, 20);
			AddTextBox(hwnd, ID_FORM_VENDA_TXT_1, NULL, 170, 100, 280, 20, 30);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_2, "Idade: ", 480, 100, 50, 20);
			AddTextBox(hwnd, ID_FORM_VENDA_TXT_2, NULL, 530, 100, 40, 20, 2);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_3, "Meia entrada para:", 50, 150, 130, 20);
			AddRadioButton(hwnd, ID_FORM_VENDA_RAD_1, "Estudante", 190, 150, 100, 20);
			AddRadioButton(hwnd, ID_FORM_VENDA_RAD_2, "Estudante Carente", 290, 150, 150, 20);
			AddRadioButton(hwnd, ID_FORM_VENDA_RAD_3, "Professor", 440, 150, 100, 20);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_4, "Selecione a atração:", 50, 200, 150, 20);
			
			Columns cols[6];
			
			strcpy(cols[0].Name, "Peça");
			cols[0].Width = 100;
			
			strcpy(cols[1].Name, "Valor");
			cols[1].Width = 100;
			
			strcpy(cols[2].Name, "Num. Vagas");
			cols[2].Width = 100;
			
			strcpy(cols[3].Name, "Data");
			cols[3].Width = 100;
			
			strcpy(cols[4].Name, "Inicio");
			cols[4].Width = 100;
			
			strcpy(cols[5].Name, "Fim");
			cols[5].Width = 100;
			
			DisplayInListView(
				AddListView(hwnd, ID_FORM_VENDA_LV_1, 50, 250, 600, 130, cols, 6),
				theaters,
				6
			);
			
			AddLabel(hwnd, ID_FORM_VENDA_LB_5, "Selecione o Assento:", 50, 400, 150, 20);
			AddComboBox(hwnd, ID_FORM_VENDA_CB_1, 200, 400, 100, 150, -1, NULL);
			
			AddButton(hwnd, ID_FORM_VENDA_BTN_1, "Confirmar", 550, 400, 100, 40);
			
			CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_3, -1);
			
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
						
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Função de venda carregada com sucesso.");
			
			break;
		}
		
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case ID_FORM_VENDA_RAD_1:
					CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_3, ID_FORM_VENDA_RAD_1);
					halfEntry = ID_FORM_VENDA_RAD_1;
					
					break;
					
				case ID_FORM_VENDA_RAD_2:
					CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_3, ID_FORM_VENDA_RAD_2);
					halfEntry = ID_FORM_VENDA_RAD_2;
					
					break;
				
				case ID_FORM_VENDA_RAD_3:
					CheckRadioButton(hwnd, ID_FORM_VENDA_RAD_1, ID_FORM_VENDA_RAD_3, ID_FORM_VENDA_RAD_3);
					halfEntry = ID_FORM_VENDA_RAD_3;
					
					break;
				
				case ID_FORM_VENDA_BTN_1:{
					int iChars = GetWindowTextLength(GetDlgItem(hwnd, ID_FORM_VENDA_TXT_1))+1;
					clientName = (char*)malloc(sizeof(char)*iChars);
					GetDlgItemText(hwnd, ID_FORM_VENDA_TXT_1, clientName, iChars);
					
					iChars = GetWindowTextLength(GetDlgItem(hwnd, ID_FORM_VENDA_TXT_2))+1;
					year = (char*)malloc(sizeof(char)*iChars);
					GetDlgItemText(hwnd, ID_FORM_VENDA_TXT_2, year, iChars);
					
					iChars = GetWindowTextLength(GetDlgItem(hwnd, ID_FORM_VENDA_CB_1))+1;
					place = (char*)malloc(sizeof(char)*iChars);
					GetDlgItemText(hwnd, ID_FORM_VENDA_CB_1, place, iChars);
					
					if (strlen(clientName) == 0) {
						MessageBox(hwnd, "Informe o nome do cliente.", "Validação", MB_OK | MB_ICONEXCLAMATION);
						
						return;
					}
					if (strlen(year) == 0) {
						MessageBox(hwnd, "Informe a idade do cliente.", "Validação", MB_OK | MB_ICONEXCLAMATION);
						
						return;
					}
					if (showSelected == -1) {
						MessageBox(hwnd, "Selecione uma peça de teatro.", "Validação", MB_OK | MB_ICONEXCLAMATION);
						
						return;
					}
					if (strlen(place) == 0) {
						MessageBox(hwnd, "Selecione um assento.", "Validação", MB_OK | MB_ICONEXCLAMATION);
						
						return;
					}
					
					int i;
					
					for(i = 0; i < 20; i += 1) {
						if (strcmp(theaters[showSelected].Places[i].Code, place) == 0) {
							break;
						}
					}
					
					tickets[ticketsCount] = CreateTicket(
						clientName,
						year,
						halfEntry,
						&theaters[showSelected],
						&theaters[showSelected].Places[i]
					);
					ticketsCount += 1;
					
					menuActive = ID_MENU_PURCHASE;
					
					CreateNewMDIChild(midClient, "Recibo de Compra", g_szChildClassName);
					
					break;
				}
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
					showSelected = nmlist->iItem;
					
					HWND cb = GetDlgItem(hwnd, ID_FORM_VENDA_CB_1);
					int i;
					
					SendMessage(cb, (UINT)CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
					
				    for (i = 0; i < 20; i += 1) {
				    	if(theaters[showSelected].Places[i].IsAvalible == FALSE) {
				    		SendMessage(cb, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT(theaters[showSelected].Places[i].Code));
						}
					}
					
					SendMessage(cb, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	            }
	        }
	        
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
