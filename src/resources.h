#ifndef defineConst
#define defineConst

/*
	Constantes para os itens de menu do sistema.
*/
#define ID_MENU_ROOT				100
#define ID_MENU_SALES				4003
#define ID_MENU_BOX					4004
#define ID_MENU_CLOSE				4005
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
		
		count = 0;
		
	    ListView_InsertItem(listView, &lv);
	    ListView_SetItemText(listView, i, 0, TEXT(theater[i].Name));
	    ListView_SetItemText(listView, i, 1, TEXT(vl));
	    ListView_SetItemText(listView, i, 2, TEXT(qt));
	    ListView_SetItemText(listView, i, 3, TEXT(theater[i].Date));
	    ListView_SetItemText(listView, i, 5, TEXT(theater[i].End));
	    ListView_SetItemText(listView, i, 4, TEXT(theater[i].Start));
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

Ticket CreateTicket(char clientName[30], char year[2], int halfEntry, TheaterShow *theater, Place *place) {
	Ticket result;
	
	strcpy(result.ClientName, clientName);
	strcpy(result.TheaterName, theater->Name);
	result.OriginalValue = theater->Value;
	
	if(halfEntry == ID_FORM_VENDA_RAD_1 || halfEntry == ID_FORM_VENDA_RAD_3) {
		strcpy(result.Discount, "50%");
	}
	
	place->IsAvalible = FALSE
	
	return result;
}

#endif
