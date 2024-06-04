#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    int* data;
    int topIndex;
} Stack;

//prototypes
Stack* InitializeStack(void);
bool IsStackEmpty(Stack* stack);
bool IsStackFull(Stack* stack);
void Push(Stack* stack, int elementNoInsert);
int Peek(Stack* stack);
int Pop(Stack* stack);

int Pop(Stack* stack){
    if(IsStackEmpty(stack)){
        printf("Stack Undeflow");
        return -1;
    }
    
    return stack->data[stack->topIndex--];
}

int Peek(Stack* stack){
    if(IsStackEmpty(stack)){
        printf("Stack Undeflow");
        return -1;
    }
    return stack->data[stack->topIndex];
}

void Push(Stack* stack, int elementToInsert){
    if(IsStackFull(stack)){
        printf("Stack Overflow");
        exit(EXIT_FAILURE);
    }
    
    stack->data[++stack->topIndex] = elementToInsert;
}

bool IsStackFull(Stack* stack){
    return stack->topIndex == MAX_SIZE - 1;
}

bool IsStackEmpty(Stack* stack){
    return stack->topIndex == -1;
}

Stack* InitializeStack(void){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(MAX_SIZE*sizeof(int));
    stack->topIndex = -1;
    return stack;
}

int main(int argc, const char * argv[]) {
    Stack* stack = InitializeStack();
    
    Push(stack, 1);
    Push(stack, 2);
    Push(stack, 3);
    Push(stack, 3);
    Push(stack, 4);
    
    printf("Popped Element: %d\n", Pop(stack));
    printf("Popped Element: %d\n", Pop(stack));
    
    printf("Peeked Element:%d\n", Peek(stack));
    
    printf("%d", stack->data[0]);
    
    // Garbage Collect
    free(stack->data);
    free(stack);
    
    return 1;
}
