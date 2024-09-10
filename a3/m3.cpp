/*
* FILE : m3.cpp
* PROJECT : SENG1050 - ASSIGNMENT 3
* PROGRAMMER : Tian Yang
* FIRST VERSION : 2024-07-16
* DESCRIPTION :
* This program compares the efficiency of searching a sorted linked list and a hash table.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_LEN 31
#define BUCKETS_SIZE 127

typedef struct SortedLinkedList SortedLinkedList;
struct SortedLinkedList
{
    char* name;
    SortedLinkedList* next;
};

enum { LINKED_LIST = 0, HASH_TABLE = 1, CONTAINER_NUM = 2 };
unsigned int generateHash(const char* name);
void insertLinkedList(const char* name, SortedLinkedList** linkedList);
void clearLinkedList(SortedLinkedList* linkedList);
const SortedLinkedList* searchLinkedList(const char* searchName, const SortedLinkedList* linkedList, int* comparisonCount);
void insertHashTable(const char* name, SortedLinkedList* hashTable[]);
void clearHashTable(SortedLinkedList* linkedList[]);
const SortedLinkedList* searchHashTable(const char* searchName, const SortedLinkedList* const hashTable[], int* comparisonCount);
void searchForNameTwice(const char* searchName, const SortedLinkedList* const hashTable[], int comparisonCount[CONTAINER_NUM], const SortedLinkedList* linkedList);

int main(void)
{
    const char* filename = "names.txt";
    FILE* txtFile = NULL;
    if (fopen_s(&txtFile, filename, "r") != 0)
    {
        fprintf(stderr, "ERROR: cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    SortedLinkedList* linkedList = NULL;
    SortedLinkedList* hashTable[BUCKETS_SIZE] = {};

    char buffer[MAX_CHAR_LEN] = "";
    while (fgets(buffer, MAX_CHAR_LEN, txtFile) != NULL)
    {
        char name[MAX_CHAR_LEN] = "";
        sscanf_s(buffer, "%[^\n]s", name, MAX_CHAR_LEN);
        insertLinkedList(name, &linkedList);
        insertHashTable(name, hashTable);
    }

    if (fclose(txtFile) != 0)
    {
        fprintf(stderr, "ERROR: cannot close file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int searchCount = 0;
    int compareInLinkedList = 0;
    int compareInHashtable = 0;
    while(printf("Search: "))
    {
        if (fgets(buffer, MAX_CHAR_LEN, stdin) == NULL || buffer[0] == '\n')
        {
            printf("End.\n\n\n\n");
            break;
        }

        searchCount++;

        char name[MAX_CHAR_LEN] = "";
        sscanf_s(buffer, "%[^\n]s", name, MAX_CHAR_LEN);

        int comparisonCount[CONTAINER_NUM] = {};
        searchForNameTwice(name, hashTable, comparisonCount, linkedList);

        compareInLinkedList += comparisonCount[LINKED_LIST];
        compareInHashtable += comparisonCount[HASH_TABLE];
    }
    printf("Number of searches: %d\n", searchCount);
    printf("Linked list comparison count: %d\n", compareInLinkedList);
    printf("Hash table comparison count: %d\n", compareInHashtable);

    clearLinkedList(linkedList);
    clearHashTable(hashTable);

    return EXIT_SUCCESS;
}

/*
* Function : generateHash
* Parameters :
*   const char* name - the string to generate hash for
* Description :
*   Generates a hash for the given string name using a simple
*   recursive algorithm.
* Return value :
*   unsigned int - the generated hash value
*/
unsigned int generateHash(const char* name)
{
    return (*name + ((*name == '\0') ? 0 : generateHash(name + 1))) % BUCKETS_SIZE;
}
/*
* Function : insertLinkedList
* Parameters :
*   const char* name - the string to be inserted
*   SortedLinkedList** linkedList - the head of the linked list
* Description :
*   Inserts a new node with the given string into the sorted linked list.
* Return value : void
*/
void insertLinkedList(const char* name, SortedLinkedList** linkedList)
{
    if (*linkedList == NULL || strcmp(name, (*linkedList)->name) < 0)
    {
        SortedLinkedList* node = *linkedList;
        
        *linkedList = (SortedLinkedList*)malloc(sizeof(SortedLinkedList));
        if (*linkedList == NULL)
        {
            fprintf(stderr, "ERROR: end of memory\n");
            exit(EXIT_FAILURE);
        }

        (*linkedList)->name = (char*)malloc(strlen(name) + 1);
        if ((*linkedList)->name == NULL)
        {
            fprintf(stderr, "ERROR: end of memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy_s((*linkedList)->name, strlen(name) + 1, name);
        
        (*linkedList)->next = node;
        return;
    }
    return insertLinkedList(name, &(*linkedList)->next);
}
/*
* Function : clearLinkedList
* Parameters :
*   SortedLinkedList* linkedList - the head of the linked list
* Description :
*   Clears the memory allocated for the linked list.
* Return value : void
*/
void clearLinkedList(SortedLinkedList* linkedList)
{
    if (linkedList == NULL) return;

    clearLinkedList(linkedList->next);
    free(linkedList->name);
    free(linkedList);
}
/*
* Function : searchLinkedList
* Parameters :
*   const char* searchName - the string to search for
*   const SortedLinkedList* linkedList - the head of the linked list
*   int* comparisonCount - pointer to store the comparison count
* Description :
*   Searches for a string in the sorted linked list and counts the comparisons made.
* Return value :
*   const SortedLinkedList* - pointer to the found node, or NULL if not found
*/
const SortedLinkedList* searchLinkedList(const char* searchName, const SortedLinkedList* linkedList, int* comparisonCount)
{
    if (linkedList == NULL)
        return NULL;
    
    (*comparisonCount)++;
    if (strcmp(searchName, linkedList->name) != 0)
        return searchLinkedList(searchName, linkedList->next, comparisonCount);
    else
        return linkedList;
}
/*
* Function : insertHashTable
* Parameters :
*   const char* name - the string to be inserted
*   SortedLinkedList* hashTable[] - the hash table
* Description :
*   Inserts a new node with the given string into the hash table.
* Return value : void
*/
void insertHashTable(const char* name, SortedLinkedList* hashTable[])
{
    insertLinkedList(name, &hashTable[generateHash(name)]);
}
/*
* Function : clearHashTable
* Parameters :
*   SortedLinkedList* hashTable[] - the hash table
* Description :
*   Clears the memory allocated for the hash table.
* Return value : void
*/
void clearHashTable(SortedLinkedList* linkedList[])
{
    for (int i = 0; i < BUCKETS_SIZE; i++) clearLinkedList(linkedList[i]);
}
/*
* Function : searchHashTable
* Parameters :
*   const char* searchName - the string to search for
*   const SortedLinkedList* const hashTable[] - the hash table
*   int* comparisonCount - pointer to store the comparison count
* Description :
*   Searches for a string in the hash table and counts the comparisons made.
* Return value :
*   const SortedLinkedList* - pointer to the found node, or NULL if not found
*/
const SortedLinkedList* searchHashTable(const char* searchName, const SortedLinkedList* const hashTable[], int* comparisonCount)
{
    return searchLinkedList(searchName, hashTable[generateHash(searchName)], comparisonCount);
}
/*
* Function : searchForNameTwice
* Parameters :
*   const char* searchName - the string to search for
*   const SortedLinkedList* const hashTable[] - the hash table
*   int comparisonCount[CONTAINER_NUM] - array to store the comparison counts
*   const SortedLinkedList* linkedList - the head of the linked list
* Description :
*   Searches for a string in both the hash table and the linked list, and prints the results.
* Return value : void
*/
void searchForNameTwice(const char* searchName, const SortedLinkedList* const hashTable[], int comparisonCount[CONTAINER_NUM], const SortedLinkedList* linkedList)
{
    const SortedLinkedList* linkedListNode = searchLinkedList(searchName, linkedList, &comparisonCount[LINKED_LIST]);
    const SortedLinkedList* hashTableNode = searchHashTable(searchName, hashTable, &comparisonCount[HASH_TABLE]);
    if (linkedListNode != NULL && hashTableNode != NULL)
    {
        printf("\t%s was found in the list in number comparisons\n", searchName);
        printf("\tlinked list: %d\n", comparisonCount[LINKED_LIST]);
        printf("\thash table bucket: %d\n", comparisonCount[HASH_TABLE]);
        putchar('\n');
    }
    else
    {
        printf("\t%s was NOT found in the list in number comparisons\n", searchName);
        putchar('\n');
    }
}