/*
* FILE : m2.cpp
* PROJECT : SENG1050 - ASSIGNMENT 2
* PROGRAMMER : Tian Yang
* FIRST VERSION : 2024-06-04
* DESCRIPTION :
* This program simulates the web browser history manager using stack and queue.
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>

#define MAX_CHAR_LEN 50

struct StackNode
{
    char* url;
    StackNode* next;
};

struct Stack
{
    StackNode* top;
};

void push(Stack* stack, const char* newUrl);
char* pop(Stack* stack);
const char* peek(const Stack* stack);
bool isEmpty(const Stack* stack);
void printStack(const StackNode* stackNode);
void releaseStack(Stack* stack);

struct QueueNode
{
    char* url;
    QueueNode* next;
};

struct Queue
{
    QueueNode* front;
    QueueNode* rear;
};

void enqueue(Queue* queue, const char* newUrl);
char* dequeue(Queue* queue);
const char* peek(const Queue* queue);
bool isEmpty(const Queue* queue);
void printQueue(const QueueNode* queueNode);
void releaseQueue(Queue* queue);

void visitNewPage(Stack* stack);
void backward(Stack* stack, Queue* queue);
void forward(Stack* stack, Queue* queue);
void displayHistory(const Stack* stack, const Queue* queue);

int main(void)
{
    Stack stack = { NULL };
    Queue queue = { NULL, NULL };

    while (true)
    {
        printf("Menu:\n");
        printf("1. Visit New Web Page\n");
        printf("2. Navigate Backward\n");
        printf("3. Navigate Forward\n");
        printf("4. Display Current Page and History\n");
        printf("5. Exit\n");
        putchar('\n');
        printf("Enter your choice: ");

        char buffer[MAX_CHAR_LEN] = "";
        fgets(buffer, MAX_CHAR_LEN, stdin);
        int number = 0;
        sscanf_s(buffer, "%1d", &number);
        
        switch (number)
        {
        case 1:
            visitNewPage(&stack);
            continue;
        case 2:
            backward(&stack, &queue);
            continue;
        case 3:
            forward(&stack, &queue);
            continue;
        case 4:
            displayHistory(&stack, &queue);
            putchar('\n');
            continue;
        case 5:
            printf("Thank you for using the web browser. Goodbye!\n");
            break;
        default:
            continue;
        }

        releaseStack(&stack);
        releaseQueue(&queue);

        break;
    }

    return 0;
}

/*
Function: push()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
    const char* newUrl: newUrl will be copid to a new created stack node.
Description: Adds a new URL to the top of the stack
Return value:
    void
*/
void push(Stack* stack, const char* newUrl)
{
    StackNode* newNode = static_cast<StackNode*>(malloc(sizeof(StackNode)));
    if (newNode == NULL)
        exit(EXIT_FAILURE);

    newNode->url = static_cast<char*>(malloc(strlen(newUrl) + 1));
    if (newNode->url == NULL)
        exit(EXIT_FAILURE);
    strcpy_s(newNode->url, strlen(newUrl) + 1, newUrl);

    newNode->next = stack->top;
    stack->top = newNode;
}

/*
Function: pop()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
Description:  Removes and returns the URL from the top of the stack.
Return value:
    char*: URL of the node.
*/
char* pop(Stack* stack)
{
    if (isEmpty(stack))
        return NULL;

    StackNode* node = stack->top;
    char* url = node->url;
    stack->top = stack->top->next;
    free(node);

    return url;
}

/*
Function: peek()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
Description: Returns the URL from the top of the stack without removing it.
Return value:
    const char*: URL of the top node.
*/
const char* peek(const Stack* stack)
{
    if (isEmpty(stack))
        return NULL;

    return stack->top->url;
}

/*
Function: isEmpty()
Parameters:
    const Stack* stack: stack holds the top pointer to a stack node.
Description: Checks if the stack is empty.
Return value:
    bool: If the stack is empty.
*/
bool isEmpty(const Stack* stack)
{
    return stack->top == NULL;
}

/*
Function: printStack()
Parameters:
    const StackNode* stackNode: Top node of a stack.
Description: Print all the URL in a stack.
Return value:
    void
*/
void printStack(const StackNode* stackNode)
{
    static int depth = 0;
    if (stackNode == NULL)
    {
        depth = 0;
        return;
    }

    printf("%d. %s\n", ++depth, stackNode->url);
    printStack(stackNode->next);
}

/*
Function: releaseStack()
Parameters:
    const Stack* stack: stack holds the top pointer to a stack node.
Description: Free all the memory of nodes in a stack.
Return value:
    void
*/
void releaseStack(Stack* stack)
{
    if (isEmpty(stack))
        return;

    free(pop(stack));
    releaseStack(stack);
}

/*
Function: enqueue()
Parameters:
    Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Adds a new URL to the rear of the queue.
Return value:
    void
*/
void enqueue(Queue* queue, const char* newUrl)
{
    QueueNode* newNode = static_cast<QueueNode*>(malloc(sizeof(QueueNode)));
    if (newNode == NULL)
        exit(EXIT_FAILURE);

    newNode->url = static_cast<char*>(malloc(strlen(newUrl) + 1));
    if (newNode->url == NULL)
        exit(EXIT_FAILURE);
    strcpy_s(newNode->url, strlen(newUrl) + 1, newUrl);
    newNode->next = NULL;

    if(isEmpty(queue))
    {
        queue->front = newNode;
    }

    if (queue->rear != NULL)
    {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
}

/*
Function: dequeue()
Parameters:
    Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Removes and returns the URL from the front of the queue.
Return value:
    char*: URL of the node.
*/
char* dequeue(Queue* queue)
{
    if(isEmpty(queue))
        return NULL;

    QueueNode* node = queue->front;
    char* url = node->url;
    queue->front = node->next;
    free(node);

    return url;
}

/*
Function: peek()
Parameters:
    const Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Returns the URL from the front of the queue without removing it
Return value:
    const char*: URL of the front node.
*/
const char* peek(const Queue* queue)
{
    if(isEmpty(queue))
        return NULL;

    return queue->front->url;
}

/*
Function: isEmpty()
Parameters:
    const Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Checks if the queue is empty.
Return value:
    bool: If the queue is empty;
*/
bool isEmpty(const Queue* queue)
{
    return queue->front == NULL;
}

/*
Function: printQueue()
Parameters:
    const QueueNode* queueNode: Front node of a queue.
Description: Print all the URL in a queue.
Return value:
    void
*/
void printQueue(const QueueNode* queueNode)
{
    static int depth = 0;
    if (queueNode == NULL)
    {
        depth = 0;
        return;
    }

    printf("%d. %s\n", ++depth, queueNode->url);
    printQueue(queueNode->next);
}

/*
Function: releaseQueue()
Parameters:
    Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Free all the memory of nodes in a queue.
Return value:
    void
*/
void releaseQueue(Queue* queue)
{
    if (isEmpty(queue))
        return;

    free(dequeue(queue));
    releaseQueue(queue);
}

/*
Function: visitNewPage()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
Description: Prompt user enter a URL to visit, and store it into a stack.
Return value:
    void
*/
void visitNewPage(Stack* stack)
{
    char buffer[MAX_CHAR_LEN] = "";
    printf("Enter the URL of the web page: ");
    fgets(buffer, MAX_CHAR_LEN, stdin);
    char url[MAX_CHAR_LEN] = "";
    sscanf_s(buffer, "%[^\n]s", url, MAX_CHAR_LEN);

    push(stack, url);

    printf("Visited: %s\n", url);
    putchar('\n');
}

/*
Function: backward()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
    Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Navigate back to the previous web page.
Return value:
    void
*/
void backward(Stack* stack, Queue* queue)
{
    char* prevPage = pop(stack);
    if (prevPage == NULL)
    {
        printf("There is no previous page!\n");
        return;
    }
    enqueue(queue, prevPage);

    printf("Previous Page: %s\n", prevPage);
    free(prevPage);
    putchar('\n');
}

/*
Function: forward()
Parameters:
    Stack* stack: stack holds the top pointer to a stack node.
    Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Navigate forward to the next web page.
Return value:
    void
*/
void forward(Stack* stack, Queue* queue)
{
    char* nextPage = dequeue(queue);
    if (nextPage == NULL)
    {
        printf("There is no next page!\n");
        return;
    }
    push(stack, nextPage);

    printf("Next Page: %s\n", nextPage);
    free(nextPage);
    putchar('\n');
}

/*
Function: displayHistory()
Parameters:
    const Stack* stack: stack holds the top pointer to a stack node.
    const Queue* queue: Queue holds the front and rear pointers to the queue nodes.
Description: Display the current web page and the browsing history.
Return value:
    void
*/
void displayHistory(const Stack* stack, const Queue* queue)
{
    const char* currentPage = peek(stack);
    if (currentPage == NULL)
    {
        printf("Current page is blank\n");
    }
    else
    {
        printf("Current Page: %s\n", currentPage);
    }
    printf("Backward History:\n");
    printStack(stack->top);
    printf("Forward History:\n");
    printQueue(queue->front);
}