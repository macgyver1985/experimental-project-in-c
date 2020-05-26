#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#ifndef functionsHelper
#define functionsHelper
HWND currentMDIChild = NULL;

/*
	Fun��o para constru��o das janelas que ser�o abertas dentro da MIDChild.
*/
HWND CreateNewMDIChild(HWND hMDIClient, char *title, const char *className)
{
	if(currentMDIChild != NULL)
		DestroyWindow(currentMDIChild);
	
	MDICREATESTRUCT mcs;

	mcs.szTitle = title;
	mcs.szClass = className;
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

/*
	Fun��o que adiciona um label na tela.
*/
HWND AddLabel(HWND context, int id, char *text, int x, int y, int width, int height)
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		"static",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
		
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	return input;
}

/*
	Fun��o que adiciona um textbox na tela.
*/
HWND AddTextBox(HWND context, int id, char *text, int x, int y, int width, int height, int maxlength)
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		"EDIT",
		text,
		WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL | WS_BORDER,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
		
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	if(maxlength != NULL)
		SendMessage(input, EM_SETLIMITTEXT, maxlength, 0);
	
	return input;
}

/*
	Fun��o que adiciona um radiobutton na tela.
*/
HWND AddRadioButton(HWND context, int id, char *text, int x, int y, int width, int height)
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | WS_BORDER,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
		
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	return input;
}

/*
	Fun��o que adiciona um combobox na tela.
*/
HWND AddComboBox(HWND context, int id, int x, int y, int width, int height, int selectedIndex, char items[][30])
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		"COMBOBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | CBN_DROPDOWN,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
		
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	if (items != NULL && sizeof(items) > 0){
		int i;
	    for (i = 0; i < sizeof(items); i += 1)
	    	SendMessage(input, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT(items[i]));
	    
		SendMessage(input, CB_SETCURSEL, (WPARAM)selectedIndex, (LPARAM)0);
	}
	
	return input;
}

/*
	Fun��o que adiciona um listbox na tela.
*/
HWND AddListBox(HWND context, int id, int x, int y, int width, int height, int selectedIndex, char items[][30])
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		"LISTBOX",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
		
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	if (items != NULL && sizeof(items) > 0){
		int i;
	    for (i = 0; i < sizeof(items); i += 1)
	    	SendMessage(input, (UINT)LB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT(items[i]));
	    
		SendMessage(input, LB_SETCURSEL, (WPARAM)selectedIndex, (LPARAM)0);
	}
	
	return input;
}

typedef struct
{
	int Width;
	char Name[20];
} Columns;

/*
	Fun��o que adiciona um listView na tela.
*/
HWND AddListView(HWND context, int id, int x, int y, int width, int height, Columns cols[])
{
	HWND input = CreateWindowEx(
	 	WS_EX_WINDOWEDGE,
		WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER,
		x, y,
		width, height,
		context,
		(HMENU)id,
		GetModuleHandle(NULL),
		NULL);
	
	if(input == NULL)
	{
		MessageBox(context, "Could not create control.", "Error", MB_OK | MB_ICONERROR);
		
		return 0;
	}
	
	ListView_SetExtendedListViewStyle(input, LVS_EX_CHECKBOXES);
	
	LVCOLUMN lvc = { 0 };
    LVITEM lv = { 0 };
	
	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
    lvc.fmt = LVCFMT_LEFT;
    
    if(sizeof(cols)/sizeof(int) > 0) {
    	int cCol;
    	
    	lvc.iSubItem = 0;
	    lvc.cx = 20;
	    lvc.pszText = NULL;
	    ListView_InsertColumn(input, 0, &lvc);
    	
    	for(cCol = 0; cCol < sizeof(cols)/sizeof(int); cCol += 1) {
    		lvc.iSubItem = cCol + 1;
    		lvc.cx = cols[cCol].Width;
    		lvc.pszText = TEXT(cols[cCol].Name);
    		ListView_InsertColumn(input, cCol + 1, &lvc);
		}
	}
	
    /* Add some rows. */
    lv.iItem = 0;
    ListView_InsertItem(input, &lv);
    ListView_SetItemText(input, 0, 1, TEXT("Friends"));
    ListView_SetItemText(input, 0, 2, TEXT("500"));
    ListView_SetCheckState(input, 0, FALSE);
// 	
//    lv.iItem = 1;
//    ListView_InsertItem(input, &lv);
//    ListView_SetItemText(input, 1, 1, TEXT("Survivor"));
//    ListView_SetItemText(input, 1, 2, TEXT("970,000"));
//    ListView_SetItemText(input, 1, 3, TEXT("Please, not again"));
//    ListView_SetCheckState(input, 1, FALSE);
	
	return input;
}
#endif
