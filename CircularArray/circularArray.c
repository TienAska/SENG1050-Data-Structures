#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

void writeToBuffer(int data, int* head, int* tail, int* circularBuffer, bool* flag)
{
	if (*flag)
	{
		printf("Buffer is full\n");
	}
	else
	{
		circularBuffer[*head] = data;
		*head = (*head + 1) % SIZE;
		if (*head == *tail) {
			*flag = true;
		}
	}
}



int main() 
{

	int head = 0;
	int tail = 0;
	int circularBuffer[5] = { 0 };
	bool is_full = false;

	writeToBuffer(10, &head, &tail, circularBuffer, &is_full);
	printf("Head = %d Tail = %d IS_FULL = %d\n", head, tail, is_full);

	return 0;
}