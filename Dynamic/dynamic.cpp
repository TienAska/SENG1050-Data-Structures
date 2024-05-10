#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)

// constants
#define FALSE 0
#define TRUE 1

// data types
struct Part 
{
	char partNumber[8];
	char name[31];
	double cost;
};

// prototypes
int getNum(void);
void clearCR(char *buf);



int main()
{
int howMany = 0;
int counter = 1;
struct Part *pAllData = NULL;
struct Part *pItem = NULL;

	// find out how much data we will be storing
	printf("How many parts are we going to process?  ");
	howMany = getNum();

	// allocate the memory for all of the input
	pAllData = (struct Part *) calloc(howMany, sizeof (struct Part));
	if( pAllData == NULL )
	{
		printf("Out of memory\n");
		return -1;
	}

	// get the input from the user
	pItem = pAllData;
	for( counter = 1; counter <= howMany; counter++ )
	{
	char costString[21] = "";

		printf("Part #%d\n", counter);

		printf("Enter part number\n");
		fgets(pItem->partNumber, sizeof pItem->partNumber, stdin);
		clearCR(pItem->partNumber);

		printf("Enter name\n");
		fgets(pItem->name, sizeof pItem->name, stdin);
		clearCR(pItem->name);

		printf("Enter cost\n");
		fgets(costString, sizeof costString, stdin);
		pItem->cost = atof(costString);

		pItem++;
	} // while( counter <= howMany )

	// display all data
	pItem = pAllData;
	printf("Parts:\n");
	for( counter = 1; counter <= howMany; counter++ )
	{
		printf("Part number: %10s, ", pItem->partNumber);
		printf("Name: %30s, ", pItem->name);
		printf("Cost: %9.2f\n", pItem->cost);

		pItem++;
	} // while( counter <= howMany )

	// free the data if it's allocated
	if( pAllData != NULL )
	{
		free(pAllData);
	}

	return 0;
}


int getNum(void)
{
char record[121] = {0};		/* record stores the string */
int number = 0;

	/* NOTE to student: indent and brace this function consistent with 
	 * your others */
	/* use fgets() to get a string from the keyboard */
	fgets(record, sizeof(record), stdin);

	/* extract the number from the string; sscanf() returns a number 
	 * corresponding with the number of items it found in the string */
	if( sscanf(record, "%d", &number) != 1 )
	{
		/* if the user did not enter a number recognizable by 
		 * the system, set number to -1 */
		number = -1;
	}

	return number;
}


void clearCR(char *buf)
{
char *whereCR = strchr(buf, '\n');
	if( whereCR != NULL ) 
	{
		*whereCR = '\0';
	}
}