#include <stdio.h>
#include <stdlib.h>	
#include <malloc.h>	

//NOTE: after reviewing this code, please check few questions at the end of the file and try to understand 
// why/how program behaves in different conditions 
int main(void)
{
	//Adding this continue while loop so that it can be tested with multiple inputs
	//No need to re-run the program
	while (true) {
		// ask user what would be the lenght of the string they want to enter
		printf("How long is the string you want to enter?\n");
		char lengthStr[10] = "";
		fgets(lengthStr, sizeof lengthStr, stdin);
		// maxInputLength also adds one for the null-termination
		int maxInputLength = atoi(lengthStr) + 1;
		printf("You entered: %d\n", maxInputLength);

		// allocate the memory, casting the return value from void * to char *
		char* pString = (char*)malloc(maxInputLength);
		if (pString == NULL)
		{
			printf("Out of memory\n");
			return -1;
		}
		// get the string from the user and then print it
		fgets(pString, maxInputLength, stdin);
		printf("You entered <%s>\n", (++pString)--);
		printf("Print the Memory Location <%p>\n", pString);
			

		// I don't need the string any more so free it
		free(pString);
	}
	return 0;
}
/*
Q1: Why this line => printf("You entered <%s>\n", pString); 
	prints in two lines.

Q2: What is the behaviour of the program when you keep following line => free(pString),
	above this line => printf("You entered <%s>\n", pString);

Q3: Now try modifing this line => char lengthStr[10] = ""; char lengthStr[3] = "";
	what would happen if you read string more than 3 characters. 

Note: Check the two "return statement", Instead of writing else followed by if statment, If pString == NULL, it will return -1  

*/