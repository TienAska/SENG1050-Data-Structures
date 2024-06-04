#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int Data;	
    struct Node* NextNode;
} Node;

typedef struct {
    Node* Front; //head
    Node* Back; //tail
} Queue;

//prototypes
Queue* InitializeQueue(void);
bool IsQueueEmpty(Queue* queue);
int Front(Queue* queue);
void EnQueue(int elementToEnqueue, Queue* queue);
int DeQueue(Queue* queue);
Node* CreateNewNode(int data);

int DeQueue(Queue* queue){
    if(IsQueueEmpty(queue)){
        printf("Queue Empty");
        return -1;
    }
    
    Node* nodeToDequeue = queue->Front;
    int elementToDequeue = nodeToDequeue->Data;
    queue->Front = nodeToDequeue->NextNode;
    free(nodeToDequeue);
    return elementToDequeue;
}

Node* CreateNewNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("No Memory");
        exit(EXIT_FAILURE);
    }
    
    newNode->Data = data;
    newNode->NextNode = NULL;
    return newNode;
}

void EnQueue(int elementToEnqueue, Queue* queue){
    Node* nodeToEnqueue = CreateNewNode(elementToEnqueue);
    
    if(IsQueueEmpty(queue)){
        queue->Front = nodeToEnqueue;
        queue->Back = nodeToEnqueue;
    } else {
        queue->Back->NextNode = nodeToEnqueue;
        queue->Back = nodeToEnqueue;
    }
}

int Front(Queue* queue){
    if(IsQueueEmpty(queue)){
        printf("Queue Empty");
        return -1;
    }
    
    return queue->Front->Data;
}

bool IsQueueEmpty(Queue* queue){
    return queue->Front == NULL;
}

Queue* InitializeQueue(void){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL){
        printf("No Memory");
        exit(EXIT_FAILURE);
    }
    
    queue->Front = NULL;
    queue->Back = NULL;
    
    return queue;
}


int main(int argc, const char * argv[]) {
    Queue* queue = InitializeQueue();
    EnQueue(10, queue);
    EnQueue(20, queue);
    EnQueue(14, queue);
    
    printf("Front Element is: %d\n", Front(queue));
    int frontElement = DeQueue(queue);
    printf("DeQueued Element is: %d\n", frontElement);
    
    printf("Front Element after DeQueue is: %d\n", Front(queue));

    return 0;
}
