#include<stdio.h>
#include<stdlib.h>

struct Student {
    int StudentId;
    int Age;
    struct Student* NextStudent;
};

//prototype
struct Student* InsertSorted(struct Student* head, int studentId, int age);
struct Student* InsertAtBeginning(struct Student* head, int studentId, int age);
void PrintList(struct Student* head);
struct Student* CreateNewNode(int studentId, int age);

struct Student* InsertSorted(struct Student* head, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId,  age);
    
    // CHECK IF THE GIVEN STUDENT ID IS SMALLER THAN THE HEAD'S STUDENT ID, THEN ADD A NEW HEAD
    if(head == NULL || head->StudentId > studentId){
        return InsertAtBeginning(head, studentId, age);
    }
    
    struct Student* current = head; //  8 < 4
    while(current->NextStudent != NULL && current->NextStudent->StudentId < studentId){
        current = current->NextStudent;
    }
    
    newStudent->NextStudent = current->NextStudent;
    current->NextStudent= newStudent;
    
    return head;
}

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

    return newStudent;
}

void PrintList(struct Student* head){
    struct Student* current = head;
    while(current != NULL){
        printf("StudentId: %d, Age: %d\n", current->StudentId, current->Age);
        printf("-------------\n");
        current = current->NextStudent;
    }
}

struct Student* InsertAtBeginning(struct Student* head, int studentId, int age){
    struct Student* newStudent = CreateNewNode(studentId, age);
    newStudent->NextStudent = head;

    return newStudent;
}



int main(void){
    //1. Let us create our HEAD element
    struct Student* studentList = NULL;

    studentList = InsertSorted(studentList, 1, 10);
    studentList = InsertSorted(studentList, 2, 20);
    studentList = InsertSorted(studentList, 8, 30);


    PrintList(studentList);
    
    printf("--------------\n");
    
    studentList = InsertSorted(studentList, 4, 40);
    
    PrintList(studentList);
}
