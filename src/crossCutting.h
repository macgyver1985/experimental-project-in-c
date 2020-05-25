#include <windows.h>
#include "resources.h"

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
