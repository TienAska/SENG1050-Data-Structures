#include<stdio.h>
#include<stdlib.h>

// 1. Define Your Struct
struct Student {
    int StudentId;
    int Age;
    struct Student* NextStudent;
};

//prototypes
struct Student* InsertAtBeginning(struct Student* head, int studentId, int age);
struct Student* InsertAtEnd(struct Student* head, int studentId, int age);
void PrintList(struct Student* head);
struct Student* CreateNewStudent(int studentId, int age);
void FreeList(struct Student* head);
int GetAgeByStudentId(struct Student* head, int studentId);


int GetAgeByStudentId(struct Student* head, int studentId){
    // itereate through the list and find the student with the supplied studentid
    // add a meaningful message (or) exception when the student id is not found
    // create a mutable variable
    struct Student* current = head;
    while(current != NULL){
        if(current->StudentId == studentId){
            return current->Age;
        }
        current = current->NextStudent;
    }
    
    printf("Student with StudentId: %d not found!", studentId);
    return -1;
}

struct Student* CreateNewStudent(int studentId, int age){
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    if(newStudent == NULL)
    {
        printf("No More Memory Space Found!!! Ran out of memory!!");
        exit(EXIT_FAILURE);
    }

    newStudent->StudentId = studentId;
    newStudent->Age = age;
    newStudent->NextStudent = NULL;
    
    return newStudent;
}

struct Student* InsertAtEnd(struct Student* head, int studentId, int age){
    struct Student* newStudent = CreateNewStudent(studentId, age);

    struct Student* current = head;
    while(current->NextStudent != NULL){
        current = current->NextStudent;
    }

    current->NextStudent = newStudent;
    return head;
}


void PrintList(struct Student* head){
    struct Student* current = head;
   
    while (current != NULL)
    {
        printf("StudentId: %d, Age: %d, NextStudent=%d\n",
         current->StudentId, current->Age, current->NextStudent);
        printf("-------------\n");
        current = current->NextStudent;
    }
}


struct Student* InsertAtBeginning(struct Student* head, int studentId, int age){
    // Request memory from heap of size equivalent to your struct Student
    struct Student* newStudent = CreateNewStudent(studentId, age);
    newStudent->NextStudent = head; // This line of code changes your actual head.

    return newStudent;
}

void FreeList(struct Student* head){
    struct Student* current = head;
    struct Student* nextStudent;
    
    while(current != NULL){
        nextStudent = current->NextStudent;
        free(current);
        current = nextStudent;
    }
}

int main(void)
{
    //2. Initialize your first student (head)
    struct Student* head = NULL;

    //3. Let us add few students at the begining of your linked list - O(1)
    head = InsertAtBeginning(head, 1, 10);
    head = InsertAtBeginning(head, 2, 20);
    head = InsertAtBeginning(head, 3, 30);

    PrintList(head);

    head = InsertAtEnd(head, 4, 40);
    printf("After Insertion at the End: \n");
    PrintList(head);
    
    int age = GetAgeByStudentId(head, 5);
    
    if(age != -1){
        printf("Student's Age: %d", age);
    }
    
    //DO GARBAGE COLLECTION
    FreeList(head);
}
