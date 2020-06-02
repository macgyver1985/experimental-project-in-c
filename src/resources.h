#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef defineConst
#define defineConst

/*
	Constantes para os itens de menu do sistema.
*/
#define ID_MENU_ROOT				100
#define ID_MENU_SALES				4003
#define ID_MENU_PURCHASE			4004
#define ID_MENU_BOX					4005
#define ID_MENU_CLOSE				4006
/*
	Constantes para a janela prícipal
*/
#define ID_MAIN_MDI					4000
#define ID_MAIN_STATUS				4001
/*
	Constantes para as MDIChilds
*/
#define ID_MDI_FIRSTCHILD			4002
/*
	Constantes da tela de venda de ingressos
*/
#define ID_FORM_VENDA_INFO			3000
#define ID_FORM_VENDA_LB_1			3001
#define ID_FORM_VENDA_TXT_1			3002
#define ID_FORM_VENDA_LB_2			3003
#define ID_FORM_VENDA_TXT_2			3004
#define ID_FORM_VENDA_LB_3			3005
#define ID_FORM_VENDA_RAD_1			3006
#define ID_FORM_VENDA_RAD_2			3007
#define ID_FORM_VENDA_RAD_3			3008
#define ID_FORM_VENDA_LB_4			3009
#define ID_FORM_VENDA_LV_1			3010
#define ID_FORM_VENDA_LB_5			3011
#define ID_FORM_VENDA_CB_1			3012
#define ID_FORM_VENDA_BTN_1			3013
/*
	Constantes da tela do comprovante
*/
#define ID_FORM_COM_INFO			5000
#define ID_FORM_COM_LB_1			5001
#define ID_FORM_COM_LB_2			5002
#define ID_FORM_COM_LB_3			5003
#define ID_FORM_COM_LB_4			5004
#define ID_FORM_COM_LB_5			5005
#define ID_FORM_COM_LB_6			5006
#define ID_FORM_COM_LB_7			5007
#define ID_FORM_COM_LB_8			5008
#define ID_FORM_COM_LB_9			5009
#define ID_FORM_COM_LB_10			5011
#define ID_FORM_COM_LB_11			5012
#define ID_FORM_COM_LB_12			5013
#define ID_FORM_COM_LB_13			5014
#define ID_FORM_COM_LB_14			5015
#define ID_FORM_COM_LB_15			5016
#define ID_FORM_COM_LB_16			5017
#define ID_FORM_COM_LB_17			5018
#define ID_FORM_COM_LB_18			5018
/*
	Constantes da tela do caixa
*/
#define ID_FORM_BOX_INFO			6000
#define ID_FORM_BOX_LV_1			6001
#define ID_FORM_BOX_LB_1			6002
#define ID_FORM_BOX_LB_2			6003
/*
	Definição de estruturas
*/
typedef struct {
	BOOL IsAvalible;
	char Code[2];
} Place;

typedef struct {
	char Name[10];
	float Value;
	char Date[10];
	char Start[10];
	char End[10];
	Place Places[20];
} TheaterShow;

TheaterShow CreateTheaterShow(char name[10], float value, char date[10], char start[10], char end[10], Place places[20]) {
	TheaterShow result;
	
	strcpy(result.Name, name);
	result.Value = value;
	strcpy(result.Date, date);
	strcpy(result.Start, start);
	strcpy(result.End, end);
	
	int i = 0;
	
	for(i; i < 20; i += 1){
		strcpy(result.Places[i].Code, places[i].Code);
		result.Places[i].IsAvalible = places[i].IsAvalible;
	}
	
	return result;
}

void DisplayInListView(HWND listView, TheaterShow theater[], int numTheater) {
	int i;
	LVITEM lv = { 0 };
	
	for(i = 0; i < numTheater; i += 1) {
		lv.iItem = i;
		
		char vl[5];
		snprintf(vl, sizeof vl, "%f", theater[i].Value);
		
		int count, ii;
		
		for(ii = 0; ii < 20; ii += 1) {
			if(theater[i].Places[ii].IsAvalible == FALSE) {
				count += 1;
			}
		}
		
		char qt[2];
		snprintf(qt, sizeof qt, "%d", count);
		
		if(count > 0) {
			ListView_InsertItem(listView, &lv);
		    ListView_SetItemText(listView, i, 0, TEXT(theater[i].Name));
		    ListView_SetItemText(listView, i, 1, TEXT(vl));
		    ListView_SetItemText(listView, i, 2, TEXT(qt));
		    ListView_SetItemText(listView, i, 3, TEXT(theater[i].Date));
		    ListView_SetItemText(listView, i, 5, TEXT(theater[i].End));
		    ListView_SetItemText(listView, i, 4, TEXT(theater[i].Start));
		}
		
		count = 0;
	}
}

typedef struct {
	char ClientName[30];
	char TheaterName[10];
	float Value;
	float OriginalValue;
	char Discount[4];
	char Date[10];
	char Start[10];
	char End[10];
	char Place[2];
	BOOL IsSold;
} Ticket;

Ticket CreateTicket(char *clientName, char *year, int halfEntry, TheaterShow *theater, Place *place) {
	Ticket result;
	
	strcpy(result.ClientName, clientName);
	strcpy(result.TheaterName, theater->Name);
	result.OriginalValue = theater->Value;
	strcpy(result.Date, theater->Date);
	strcpy(result.Start, theater->Start);
	strcpy(result.End, theater->End);
	strcpy(result.Place, place->Code);
	result.IsSold = TRUE;
	
	int y = atoi(year);
	
	if(halfEntry == ID_FORM_VENDA_RAD_1 || (halfEntry == ID_FORM_VENDA_RAD_2 && strcmp(theater->Date, "Terça") != 0) || halfEntry == ID_FORM_VENDA_RAD_3 || y >= 60 || y <= 12) {
		strcpy(result.Discount, "50%");
		result.Value = theater->Value * 0.5;
	} else if(halfEntry == ID_FORM_VENDA_RAD_2 && strcmp(theater->Date, "Terça") == 0) {
		strcpy(result.Discount, "100%");
		result.Value = 0;
	} else {
		strcpy(result.Discount, "0%");
		result.Value = theater->Value;
	}
	
	place->IsAvalible = TRUE;
	
	return result;
}

void DisplayTicketsInListView(HWND listView, Ticket tickets[], int num) {
	int i;
	LVITEM lv = { 0 };
	
	for(i = 0; i < num; i += 1) {
		if(tickets[i].IsSold == FALSE) {
			break;
		}
		
		lv.iItem = i;
		ListView_InsertItem(listView, &lv);
		ListView_SetItemText(listView, i, 0, TEXT(tickets[i].ClientName));
		ListView_SetItemText(listView, i, 1, TEXT(tickets[i].TheaterName));
		
		char vl[5];
		snprintf(vl, sizeof vl, "%f", tickets[i].OriginalValue);
		
	    ListView_SetItemText(listView, i, 2, TEXT(vl));
	    ListView_SetItemText(listView, i, 3, TEXT(tickets[i].Discount));
	    
	    snprintf(vl, sizeof vl, "%f", tickets[i].Value);
	    
	    ListView_SetItemText(listView, i, 4, TEXT(vl));
	}
}

#endif
