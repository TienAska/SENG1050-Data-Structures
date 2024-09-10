/*
* FILE : m1.cpp
* PROJECT : SENG1050 - ASSIGNMENT 1
* PROGRAMMER : Tian Yang
* FIRST VERSION : 2024-06-02
* DESCRIPTION :
* This program takes in information about flights and stores the destination, fare 
* and date in double linked-list to be displayed. Dynamic memory allocation is used
* to store the strings in the struct.
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cfloat>

#define MAX_CHAR_LEN 30

struct FlightNode
{
    char* dest;
    char* date;
    float fare;
    FlightNode* prev;
    FlightNode* next;
};

enum SORT_BY { FARE, DEST };

FlightNode* newFlight(const char* dest, const char* date, float fare, FlightNode* prev = nullptr, FlightNode* next = nullptr);
void insertSortedFlight(FlightNode** head, FlightNode** tail, FlightNode* node, SORT_BY sort);
void freeFlights(FlightNode* head);

FlightNode* findFlight(FlightNode* head, const char* dest, const char* date);
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail);

void printFlights(const FlightNode* head);

int main(void)
{
    FlightNode* flightByFareHead = nullptr;
    FlightNode* flightByFareTail = nullptr;
    FlightNode* flightByDestHead = nullptr;
    FlightNode* flightByDestTail = nullptr;

    char buffer[MAX_CHAR_LEN] = "";
    while (true)
    {
        static int i = 0;
        printf("Please input flight info #%d\n", ++i);

        printf("Destination:");
        fgets(buffer, MAX_CHAR_LEN, stdin);
        char dest[MAX_CHAR_LEN] = "";
        sscanf_s(buffer, "%[^\n]s", dest, MAX_CHAR_LEN);
        if (dest[0] == '.')
            break;


        printf("Date:");
        fgets(buffer, MAX_CHAR_LEN, stdin);
        char date[MAX_CHAR_LEN] = "";
        sscanf_s(buffer, "%[^\n]s", date, MAX_CHAR_LEN);
        if (date[0] == '.')
            break;

        printf("Fare:");
        fgets(buffer, MAX_CHAR_LEN, stdin);
        float fare = 0.0f;
        sscanf_s(buffer, "%f", &fare);

        insertSortedFlight(&flightByFareHead, &flightByFareTail, newFlight(dest, date, fare), FARE);
        insertSortedFlight(&flightByDestHead, &flightByDestTail, newFlight(dest, date, fare), DEST);

        printf("\n");
    }
    printf("\n");

    printf("------------------------------------\n");
    printf("Flight list sorted by fare:\n");
    printFlights(flightByFareHead);

    printf("Flight list sorted by destination:\n");
    printFlights(flightByDestHead);
    printf("------------------------------------\n");

    printf("\n");
    printf("\n");
    printf("\n");

    printf("Please input flight for search\n");

    printf("Destination:");
    fgets(buffer, MAX_CHAR_LEN, stdin);
    char dest[MAX_CHAR_LEN] = "";
    sscanf_s(buffer, "%[^\n]s", dest, MAX_CHAR_LEN);

    printf("Date:");
    fgets(buffer, MAX_CHAR_LEN, stdin);
    char date[MAX_CHAR_LEN] = "";
    sscanf_s(buffer, "%[^\n]s", date, MAX_CHAR_LEN);

    FlightNode* foundFlight = findFlight(flightByDestHead, dest, date);
    if (foundFlight)
    {
        printf("Found this flight with fare: %f\n", foundFlight->fare);

        printf("New fare:");
        fgets(buffer, MAX_CHAR_LEN, stdin);
        float fare = 0.0f;
        sscanf_s(buffer, "%f", &fare);
        if (fabs(foundFlight->fare - fare) <= FLT_EPSILON)
        {
            printf("This fare does not change\n");
        }
        else
        {
            foundFlight->fare = fare;

            foundFlight = findFlight(flightByFareHead, dest, date);
            deleteNode(foundFlight, &flightByFareHead, &flightByFareTail);
            insertSortedFlight(&flightByFareHead, &flightByFareTail, newFlight(dest, date, fare), FARE);
        }
    }
    else
    {
        printf("Did not find this flight\n");
    }

    printf("\n");

    printf("------------------------------------\n");
    printf("Flight list sorted by fare:\n");
    printFlights(flightByFareHead);

    printf("Flight list sorted by destination:\n");
    printFlights(flightByDestHead);
    printf("------------------------------------\n");

    printf("\n");

    freeFlights(flightByFareHead);
    freeFlights(flightByDestHead);

    return 0;
}

/*
Function: newFlight()
Parameters:
    const char* dest: destination of flight
    const char* date: date of flight
    float fare: fare of flight
    FlightNode* prev: pointer to the previous node
    FlightNode* next: pointer to the next node
Description: This function takes flight info and dynamic allocate memory to make a new node.
Return value: 
    FlightNode*: pointer to the new node.
*/
FlightNode* newFlight(const char* dest, const char* date, float fare, FlightNode* prev /*= nullptr*/, FlightNode* next /*= nullptr*/)
{
    FlightNode* node = static_cast<FlightNode*>(malloc(sizeof(FlightNode)));
    if (node == nullptr) return nullptr;

    node->dest = static_cast<char*>(malloc(strlen(dest) + 1));
    if (node->dest == nullptr) return nullptr;

    node->date = static_cast<char*>(malloc(strlen(date) + 1));
    if (node->date == nullptr) return nullptr;

    strcpy_s(node->dest, strlen(dest) + 1, dest);
    strcpy_s(node->date, strlen(date) + 1, date);
    node->fare = fare;
    node->prev = prev;
    node->next = next;

    return node;
}

/*
Function: insertSortedFlight()
Parameters:
    FlightNode** head: pointer to pointer to a head of the list.
    FlightNode** tail: pointer to pointer to a tail of the list.
    FlightNode* node: pointer to the node to be insert.
    SORT_BY sort: sort type.
Description: This function inserts a node between the given head and tail of a list. Sorted by
destination or fare.
Return value:
    void
*/
void insertSortedFlight(FlightNode** head, FlightNode** tail, FlightNode* node, SORT_BY sort)
{
    if (node == nullptr) return;

    if ((*head) == nullptr)
    {
        *head = node;
        *tail = node;
        return;
    }

    bool greaterOrEqual = false;
    if (sort == FARE)
        greaterOrEqual = (node->fare - (*head)->fare) >= FLT_EPSILON;
    else if (sort == DEST)
        greaterOrEqual = strcmp(node->dest, (*head)->dest) >= 0;
    else
        return;

    if (greaterOrEqual)
    {
        if ((*head)->next != nullptr)
        {
            insertSortedFlight(&(*head)->next, tail, node, sort);
        }
        else // Insert to the tail.
        {
            node->prev = *head;
            node->next = nullptr;
            (*head)->next = node;
            *tail = node;
        }
    }
    else // Insert to the head.
    {
        node->prev = (*head)->prev;
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    }
}

/*
Function: freeFlights()
Parameters:
    FlightNode* head: pointer the head of list.
Description: This function free all the nodes of a list recursively.
Return value:
    void
*/
void freeFlights(FlightNode* head)
{
    if (head == nullptr) return;

    freeFlights(head->next);
    free(head->dest);
    free(head->date);
    free(head);
}

/*
Function: insertSortedFlight()
Parameters:
    FlightNode* head: head of list
    char* destination: pointer to null-terminated string containing destination
    char* date: pointer to null-terminated string containing date
Description: This function finds a node in a linked-list. Return the pointer when
the destination and the date string are both matched.
Return value:
    FlightNode*: pointer to the found node.
*/
FlightNode* findFlight(FlightNode* head, const char* dest, const char* date)
{
    if (head == nullptr) return nullptr;

    if ((strcmp(head->dest, dest) == 0) && (strcmp(head->date, date) == 0))
        return head;
    else
        return findFlight(head->next, dest, date);
}

/*
Function: deleteNode()
Parameters:
    FlightNode* node: node to delete
    FlightNode** head: pointer to head of list
    FlightNode** tail: pointer to tail of list
Description: This function delete a node of a linked-list, and reconnect the
previous and next node.
Return value:
    void
*/
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail)
{
    if (node == nullptr) return;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        *head = node->next;
    
    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        *tail = node->prev;

    free(node->dest);
    free(node->date);
    free(node);
}


/*
Function: deleteNode()
Parameters:
    const FlightNode* head: head pointer to a list
Description: This function print all flight information in a list recursively.
Return value:
    void
*/
void printFlights(const FlightNode* head)
{
    if (head == nullptr) return;

    printf("Destination: %-35sDate: %-35sFare:%f\n", head->dest, head->date, head->fare);

    printFlights(head->next);
}

