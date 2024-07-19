#include <stdio.h>
#include <stdlib.h>

struct Student {
    int StudentId;
    struct Student* NextStudent;
};

//prototypes
struct Student* CreateNewStudent(int studentId);
void InsertNewStudentAtTheBeginning(struct Student** head, struct Student** tail, int studentId);
//void InsertNewStudentAtTheEnd(struct Student** head, struct Student** tail, int studentId);
//void DeleteStudentFromTheBeginning(struct Student** head, struct Student** tail);
void DeleteStudentFromTheEnd(struct Student** head, struct Student** tail);
void PrintList(struct Student* head);

void PrintList(struct Student* head){
    if (head == NULL) {
        printf("Empty list!\n");
        return;
    }
    
    struct Student* current = head;
    
    
    do {
        printf("Student ID: %d\n", current->StudentId);
        current = current->NextStudent;
    } while(current != head);

}

void DeleteStudentFromTheEnd(struct Student** head, struct Student** tail){
    if (*head == NULL)
    {
        printf("List is empty");
        
        return;
    }
    
    struct Student* studentToBeDeleted = *tail;
    
    if(*head == *tail)
    {
        free(studentToBeDeleted);
        *head = NULL;
        *tail = NULL;
        
        return;
    }
    
    struct Student* secondLastElement = *head;
    
    while(secondLastElement->NextStudent != *tail){
        secondLastElement = secondLastElement->NextStudent;
    }
    secondLastElement->NextStudent = *head;
    *tail = secondLastElement;
    free(studentToBeDeleted);
    
}

void InsertNewStudentAtTheBeginning(struct Student** head, struct Student** tail, int studentId){
    struct Student* newStudent = CreateNewStudent(studentId);
    
    if (*head == NULL) {
        *head = newStudent;
        *tail = newStudent;
        newStudent->NextStudent = newStudent;
        
        return;
    }
    
    newStudent->NextStudent = *head;
    (*tail)->NextStudent = newStudent;
    *head = newStudent;
    
}


struct Student* CreateNewStudent(int studentId){
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("No Memory Available");
        exit(EXIT_FAILURE);
    }
    
    newStudent->StudentId = studentId;
    newStudent->NextStudent = NULL;
    
    return newStudent;
}


int main(int argc, const char * argv[]) {
    struct Student* head = NULL;
    struct Student* tail = NULL;
    
    InsertNewStudentAtTheBeginning(&head, &tail, 50);
    InsertNewStudentAtTheBeginning(&head, &tail, 100);
    InsertNewStudentAtTheBeginning(&head, &tail, 75);
    
    printf("Printing after Insert Head: \n");
    PrintList(head);
    printf("------------\n");
    
    
    printf("Printing after Insert Tail: \n");
    //InsertNewStudentAtTheEnd(&head, &tail, 80);
    PrintList(head);
    printf("------------\n");
    
    printf("Printing after Delete Head: \n");
    //DeleteStudentFromTheBeginning(&head, &tail);
    PrintList(head);
    printf("------------\n");
    
    printf("Printing after Delete Tail: \n");
    DeleteStudentFromTheEnd(&head, &tail);
    DeleteStudentFromTheEnd(&head, &tail);
    DeleteStudentFromTheEnd(&head, &tail);
    PrintList(head);
    printf("------------\n");
    return 0;
}
