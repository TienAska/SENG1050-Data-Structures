#include<stdio.h>
#include<stdlib.h>

struct Student {
    int StudentId;
    int Age;
    struct Student* NextStudent;
    struct Student* PrevStudent;
};

//prototype
struct Student* InsertSorted(struct Student* head, struct Student** tail, int studentId, int age);
struct Student* InsertAtBeginning(struct Student* head, struct Student** tail, int studentId, int age);
void PrintListForward(struct Student* head);
void PrintListBackward(struct Student* tail);
struct Student* CreateNewNode(int studentId, int age);

struct Student* InsertSorted(struct Student* head, struct Student** tail, int studentId, int age) {
    //Case 1 - List is empty
    struct Student* newStudent = CreateNewNode(studentId, age);
    if (head == NULL) {        
        *tail = newStudent;
        return newStudent;
    }
    //struct Student* newStudent = CreateNewNode(studentId, age);
    //Case 2 - Only one node in the list i.e. Head = Tail
    if (head == *tail)
    {
        if (head->StudentId > studentId)
        {
            //add before the node, no need to move tail, need to move the head 
            newStudent->NextStudent = head;
            head->PrevStudent = newStudent;
            head = newStudent;
        }
        else
        {
            //add after the node, no need to move head, need to move the tail
            head->NextStudent = newStudent;
            *tail = newStudent;
            newStudent->PrevStudent = head;
        }
        return head;
    }
    else
    {
        struct Student* curr = head;
        if (curr->StudentId > studentId)
        {
            //add before the node, no need to move tail, need to move the head 
            newStudent->NextStudent = curr;
            curr->PrevStudent = newStudent;
            curr = newStudent;
            head = curr;
        }
        else
        {
            while (curr->NextStudent != NULL && curr->NextStudent->StudentId < studentId) {
                curr = curr->NextStudent;
            }
            //two possibilites can happen, curr may point to tail or curr point to anywhere in between
            if (curr == *tail)
            {
                curr->NextStudent = newStudent;
                newStudent->PrevStudent = curr;
                *tail = curr->NextStudent;
            }
            else 
            {
                //curr->NextStudent = newStudent;
                struct Student* ptr = curr->NextStudent;
                newStudent->PrevStudent = curr;
                newStudent->NextStudent = curr->NextStudent;
                ptr->PrevStudent = newStudent;
                curr->NextStudent = newStudent;
            }

        }
        return head;
    }

    

    /*struct Student* current = head; //  8 < 4
    while (current->NextStudent != NULL && current->NextStudent->StudentId < studentId) {
        current = current->NextStudent;
    }

    newStudent->NextStudent = current->NextStudent;
    current->NextStudent = newStudent;

    return head;
    */
}

struct Student* CreateNewNode(int studentId, int age) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

    // Memory Validation
    if (newStudent == NULL) {
        printf("No more memory available!!!");
        exit(EXIT_FAILURE);
    }

    newStudent->StudentId = studentId;
    newStudent->Age = age;
    newStudent->NextStudent = NULL;
    newStudent->PrevStudent = NULL;

    return newStudent;
}

void PrintListForward(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        printf("StudentId: %d, Age: %d\n", current->StudentId, current->Age);
        current = current->NextStudent;
    }
}

void PrintListBackward(struct Student* tail) {
    struct Student* current = tail;
    while (current != NULL) {
        printf("StudentId: %d, Age: %d\n", current->StudentId, current->Age);
        current = current->PrevStudent;
    }
}

struct Student* InsertAtBeginning(struct Student* head, int studentId, int age) {
    struct Student* newStudent = CreateNewNode(studentId, age);
    return newStudent;
}



int main(void) {
    //1. Let us create our HEAD element
    struct Student* head = NULL;
    struct Student* tail = NULL;

    head = InsertSorted(head, &tail, 2, 20);
    head = InsertSorted(head, &tail, 8, 30);
    head = InsertSorted(head, &tail, 1, 10);
    head = InsertSorted(head, &tail, 4, 40);
    

    printf("print forward\n");
    PrintListForward(head);
    printf("print backward\n");
    PrintListBackward(tail);

    
    
}
