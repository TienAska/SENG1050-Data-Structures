#include <stdio.h>
#include <stdlib.h>	
#include <malloc.h>	
#include <string.h>
#include <conio.h>

#pragma warning(disable:4996)

struct Part
{
	char partNumber[8];
	char name[30];
	double cost;

	struct Part* next;
};

//prototypes

void clearNewLineChr(char* buf);
Part *createNewNode(Part *newHead);
void displayPartInfo(Part *head);
Part *deletePartList(Part *head);

int main()
{
	char key = 0;
	#define kEnter    '1'
	#define kList     '2'
	#define kDelete   '3'
	#define kQuit     '4'
	#define kLoopForever   1 
	//This would point to the beginning of the list
	struct Part* head = NULL;


	while (kLoopForever)
	{
		//User Menu to perform specific action
		printf("\n\nMenu\n\n");
		printf("%c . . . Enter new info\n", kEnter);
		printf("%c . . . List all info\n", kList);
		printf("%c . . . Delete all info\n", kDelete);
		printf("%c . . . Quit\n", kQuit);
		printf("Enter your choice . . .");

		key = getch();
		if (key == kQuit)
		{
			break;
		}

		switch (key)
		{
		case kEnter:
			head = createNewNode(head);
			break;

		case kList:
			displayPartInfo(head);
			break;

		case kDelete:
			 head = deletePartList(head);
			break;

		default:
			printf("\nInvalid choice\n");
			break;
		}	/* end switch */
	}
	
	return 0;
}

//Prototypes definition

/*
* Function: void clearNewLineChr(char *str)
*
* Description: This function will get rid of a \n at the end of a string (from fgets) and adds '\0'
*			   If there isn't one, it doesn't change the string.
*
* Parameter: char *str: start of the string
* Return Value: nothing
*/

void clearNewLineChr(char* buf)
{
	char* whereCr = strchr(buf, '\n');
	if (whereCr != NULL)
	{
		*whereCr = '\0';
	}
}

/*
* Function: Part* createNewNode(Part* newHead)
*
* Description: This function will add new block data to the end of the list,
				It also alocates memory for new Part and allow user to enter data related 
				to new Part.
*
* Parameter: Part *head: start of the list
* Return Value: Part *head: return same head pointer
*/

Part* createNewNode(Part* newHead)
{
	//we need two more pointers 
// 1. newBlock => points to user supplied data
// 2. ptr => this one is used to traverse across the list

	struct Part* newBlock = NULL;
	struct Part* ptr = NULL;

	// allocate a block of memory for newBlock
	newBlock = (Part*)malloc(sizeof(Part));
	//chck if memory is allocated or not
	if (newBlock == NULL)
	{
		printf("Error! No memory available \n");
		return newHead;
	}
	// Read the data from user and put into newly created block
	char costString[20] = "";
	printf("Enter part number \n");
	fgets(newBlock->partNumber, sizeof(newBlock->partNumber), stdin);
	clearNewLineChr(newBlock->partNumber);


	printf("Enter part name \n");
	fgets(newBlock->name, sizeof(newBlock->name), stdin);
	clearNewLineChr(newBlock->name);

	printf("Enter cost \n");
	fgets(costString, sizeof(costString), stdin);
	newBlock->cost = atof(costString);

	newBlock->next = NULL;

	//Now you have datablock, attach it to the Link List

	if (newHead == NULL)
	{
		newHead = newBlock;
	}
	else
	{
		ptr = newHead;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = newBlock;

	}	
	return newHead;
}

/*
* Function: void displayPartInfo(Part* head)
*
* Description: This function will take head pointer and iterate over the list and display List data
*
* Parameter: Part *head: start of the list
* Return Value: void
*/

void displayPartInfo(Part *head)
{
	Part* ptr = head;
	//Iterate over the list and print the data, please add few lines of code below

	while (ptr != NULL) 
	{
		printf("\n");
		printf("PartNumber:         %s\n", ptr->partNumber);
		printf("Name:      %s\n", ptr->name);
		printf("Price: %f\n\n", ptr->cost);
		ptr = ptr->next;
	}

	printf("\n\n<End of data>\n");
}


Part *deletePartList(Part* head)
{
	Part* curr = NULL;
	Part* ptr = head;
	while(ptr != NULL)
	{
		//first point curr to ptr => current block,
		curr = ptr;
		//move ptr to next block
		ptr = ptr->next;
		//free curr block
		free(curr);
	}
	// after removing all the blocks there is nothing left in list
	// head would be NULL
	return NULL;
}
