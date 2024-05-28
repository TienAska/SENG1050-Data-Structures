#include <stdio.h>
#include <stdlib.h>

struct Student {
    int StudentId;
    int Age;
    struct Student* PreviousStudent;
    struct Student* NextStudent;
};

struct Student* InsertNewHead(struct Student* head, struct Student** tail, int studentId, int age);
struct Student* InsertNewTail(struct Student* tail, int studentId, int age);
void PrintList(struct Student* head);
void FreeList(struct Student* head);
struct Student* CreateNewNode(int studentId, int age);


struct Student* CreateNewNode(int studentId, int age){
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    // Memory Validation
    if(newStudent == NULL){
        printf("No more memory available!!!");
        exit(EXIT_FAILURE);
    }

    newStudent->StudentId = studentId;
    newStudent->Age = age;
    newStudent->NextStudent = NULL;
    newStudent->PreviousStudent = NULL;

    return newStudent;
}

struct Student* InsertNewHead(struct Student* head, struct Student** tail, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId, age);
    
    if(head == NULL){
        *tail = newStudent;
        return newStudent;
    }
    
    newStudent->NextStudent = head;
    head->PreviousStudent = newStudent;
    
    return newStudent;
}

struct Student* InsertNewTail(struct Student* tail, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId, age);
    
    if(tail == NULL){
        return newStudent;
    }
    
    tail->NextStudent = newStudent;
    newStudent->PreviousStudent = tail;
    
    return newStudent;
}


void FreeList(struct Student* head){
    
    struct Student* current = head;
    struct Student* tempNode;
    
    while (current != NULL) {
        tempNode = current->NextStudent;
        free(current);
        current = tempNode;
    }
    
}


void PrintList(struct Student* head){
    struct Student* current = head;
    while(current != NULL){
        printf("StudentId: %d, Age:%d\n", current->StudentId, current->Age);
        printf("-------------\n");
        current = current->NextStudent;
    }
}


int main(void) {
    struct Student* head = NULL;
    struct Student* tail = NULL;
    
    head = InsertNewHead(head, &tail, 1, 10);
    
    head = InsertNewHead(head, &tail, 2, 20);
    head = InsertNewHead(head, &tail, 3, 30);
    
    PrintList(head);
    
    tail = InsertNewTail(tail, 4, 40);
    
    printf("-----------------\n");
    
    PrintList(head);
    
    FreeList(head);
    return 0;
}
