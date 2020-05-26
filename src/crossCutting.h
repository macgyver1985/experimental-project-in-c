#include <windows.h>

#ifndef functionsHelper
#define functionsHelper
HWND currentMDIChild = NULL;

/*
	Função para construção das janelas que serão abertas dentro da MIDChild.
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
	Função que adiciona um label na tela.
*/
HWND AddLabel(HWND context, int *id, char *text, int x, int y, int width, int height)
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
	Função que adiciona um textbox na tela.
*/
HWND AddTextBox(HWND context, int *id, char *text, int x, int y, int width, int height, int maxlength)
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
	Função que adiciona um radiobutton na tela.
*/
HWND AddRadioButton(HWND context, int *id, char *text, int x, int y, int width, int height)
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
	Função que adiciona um label na tela.
*/
HWND AddComboBox(HWND context, int *id, int x, int y, int width, int height, char items[][30])
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
	    
		SendMessage(input, LB_SETCURSEL, (WPARAM)2, (LPARAM)0);
	}
	
	return input;
}
#endif
