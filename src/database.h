#include "resources.h"

#ifndef database
#define database

Place places[20];
TheaterShow theaters[6];
Ticket tickets[120];
int ticketsCount = 0;

void LoadDataBase() {
	// Carrega os assentos para as peças de teatro.
	strcpy(places[0].Code, "A1");
	places[0].IsAvalible = FALSE;
	
	strcpy(places[1].Code, "A2");
	places[1].IsAvalible = FALSE;
	
	strcpy(places[2].Code, "A3");
	places[2].IsAvalible = FALSE;
	
	strcpy(places[3].Code, "A4");
	places[3].IsAvalible = FALSE;
	
	strcpy(places[4].Code, "A5");
	places[4].IsAvalible = FALSE;
	
	strcpy(places[5].Code, "B1");
	places[5].IsAvalible = FALSE;
	
	strcpy(places[6].Code, "B2");
	places[6].IsAvalible = FALSE;
	
	strcpy(places[7].Code, "B3");
	places[7].IsAvalible = FALSE;
	
	strcpy(places[8].Code, "B4");
	places[8].IsAvalible = FALSE;
	
	strcpy(places[9].Code, "B5");
	places[9].IsAvalible = FALSE;
	
	strcpy(places[10].Code, "C1");
	places[10].IsAvalible = FALSE;
	
	strcpy(places[11].Code, "C2");
	places[11].IsAvalible = FALSE;
	
	strcpy(places[12].Code, "C3");
	places[12].IsAvalible = FALSE;
	
	strcpy(places[13].Code, "C4");
	places[13].IsAvalible = FALSE;
	
	strcpy(places[14].Code, "C5");
	places[14].IsAvalible = FALSE;
	
	strcpy(places[15].Code, "D1");
	places[15].IsAvalible = FALSE;
	
	strcpy(places[16].Code, "D2");
	places[16].IsAvalible = FALSE;
	
	strcpy(places[17].Code, "D3");
	places[17].IsAvalible = FALSE;
	
	strcpy(places[18].Code, "D4");
	places[18].IsAvalible = FALSE;
	
	strcpy(places[19].Code, "D5");
	places[19].IsAvalible = FALSE;
	
	// Carrega as peças disponíveis
	theaters[0] = CreateTheaterShow("Peça 1", 30, "Terça", "17:00", "18:00", places);
	theaters[1] = CreateTheaterShow("Peça 2", 80, "Terça", "18:30", "20:00", places);
	theaters[2] = CreateTheaterShow("Peça 3", 50, "Terça", "20:30", "23:00", places);
	theaters[3] = CreateTheaterShow("Peça 1", 30, "Sexta", "17:00", "18:00", places);
	theaters[4] = CreateTheaterShow("Peça 2", 80, "Sexta", "18:30", "20:00", places);
	theaters[5] = CreateTheaterShow("Peça 3", 50, "Sexta", "20:30", "23:00", places);
}

#endif
