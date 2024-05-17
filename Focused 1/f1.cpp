/*
* FILE : f1.cpp
* PROJECT : SENG1050 - FOCUSED ASSIGNMENT 1
* PROGRAMMER : Tian Yang
* FIRST VERSION : 2024-05-11
* DESCRIPTION :
* This program takes in information about flights and stores the destination and
* date in an array of structs to be displayed. Dynamic memory allocation is used 
* to store the strings in the struct.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

struct FlightInfo
{
	char* destination;
	char* date;
};

void fillFlightInfo(FlightInfo* flight, const char* destination, const char* date);
void printFlightInfo(FlightInfo* flights, int size);

int main()
{
	FlightInfo flights[10] = {};

	for (int i = 0; i < 10; i++)
	{
		printf("Please input flight info #%d/10\n", i + 1);
		printf("Destination:");
		char buffer[30] = "";
		fgets(buffer, 30, stdin);
		char destination[30] = "";
		sscanf_s(buffer, "%[^\n]s", destination, 30);


		printf("Date:");
		fgets(buffer, 30, stdin);
		char date[30] = "";
		sscanf_s(buffer, "%[^\n]s", date, 30);

		fillFlightInfo(&flights[i], destination, date);

		printf("\n");
	}

	printf("\n");
	printFlightInfo(flights, 10);

	for (int i = 0; i < 10; i++)
	{
		free(flights[i].destination);
		flights[i].destination = NULL;
		free(flights[i].date);
		flights[i].date = NULL;
	}

	return 0;
}

/*
Function: fillFlightInfo()
Parameters: 
	FlightInfo* flight: 
	const char* destination:
	const char* date:
Description: This function takes a pointer to a struct FlightInfo and the
destination and date information as parameters and fills in the struct's fields.
Return value: void
*/
void fillFlightInfo(FlightInfo* flight, const char* destination, const char* date)
{
	flight->destination = (char*)malloc(strlen(destination) + 1);
	strcpy_s(flight->destination, strlen(destination) + 1, destination);

	flight->date = (char*)malloc(strlen(date) + 1);
	strcpy_s(flight->date, strlen(date) + 1, date);
}

/*
Function: printFlightInfo()
Parameters:
	FlightInfo* flight:
	int size:
Description: This function takes the array of structs as a parameter and
prints all of the information contained within the array in a nicely-formatted
fashion, one flight per line.
Return value: void
*/
void printFlightInfo(FlightInfo* flights, int size)
{
	printf("%-35s%-35s\n\n", "Destination:", "Date:");

	for (int i = 0; i < size; i++)
	{
		printf("%-35s%-35s\n", flights[i].destination, flights[i].date);
	}
}

