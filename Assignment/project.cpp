/*
 * FILE : project.cpp
 * PROJECT : SENG1050 - Project
 * PROGRAMMER : Tian Yang
 * FIRST VERSION : 2024-08-12
 * DESCRIPTION :
 *   This program implements a parcel management system using a hash table
 *   of binary search trees. It allows users to enter and query parcel
 *   information based on destination country and weight.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define CHECK_ALLOC(call)                          \
do                                                 \
{                                                  \
    if (call)                                      \
    {                                              \
        fprintf(stderr, "ERROR: end of memory\n"); \
        exit(EXIT_FAILURE);                        \
    }                                              \
} while (false)

#define CHECK_FILE(call)                              \
do                                                    \
{                                                     \
    if (call)                                         \
    {                                                 \
        fprintf(stderr, "ERROR: cannot open file\n"); \
        exit(EXIT_FAILURE);                           \
    }                                                 \
} while (false)

#define MAX_CHAR_LEN 21
#define BUCKETS_SIZE 127

#define GET_BST(hashTable, key) hashTable[hash((unsigned char*)key) % BUCKETS_SIZE]

unsigned long hash(unsigned char* str);
void promptCountry(char* output);
void promptWeight(int* output);

typedef struct Parcel
{
    char* destination;
    int weight;
    float value;
    Parcel* left;
    Parcel* right;
} Parcel;

Parcel* insertBST(Parcel* node, const char* destination, int weight, float value);
void freeBST(Parcel* node);
void printParcel(const Parcel* node);
void printBST(const Parcel* node);
void printBSTHigher(const Parcel* node, int weight);
void printBSTLower(const Parcel* node, int weight);
int overallWeight(const Parcel* node);
float overallValue(const Parcel* node);
const Parcel* cheapest(const Parcel* node);
const Parcel* mostExpensive(const Parcel* node);
const Parcel* lightest(const Parcel* node);
const Parcel* heaviest(const Parcel* node);

int main(void)
{
    Parcel* hashTable[BUCKETS_SIZE] = {};

    const char* filename = "couriers.txt";
    FILE* file = NULL;
    CHECK_FILE(fopen_s(&file, filename, "r") != 0);

    char buffer[BUFSIZ] = "";
    while (fgets(buffer, BUFSIZ, file) != NULL)
    {
        char destination[MAX_CHAR_LEN] = "";
        int weight = 0;
        float value = 0.0f;
        sscanf_s(buffer, "%20[^,],%d,%f", destination, MAX_CHAR_LEN, &weight, &value);

        Parcel** hashBucket = &GET_BST(hashTable, destination);
        *hashBucket = insertBST(*hashBucket, destination, weight, value);
    }

    while (true)
    {
        printf("Menu:\n");
        printf("1. Enter country name and display all the parcels details\n");
        printf("2. Enter country and weight pair\n");
        printf("3. Display the total parcel load and valuation for the country\n");
        printf("4. Enter the country name and display cheapest and most expensive parcel's details\n");
        printf("5. Enter the country name and display lightest and heaviest parcel for the country.\n");
        printf("6. Exit the application.\n");
        printf("Enter a number of the menu: ");
        fgets(buffer, BUFSIZ, stdin);
        int number = 0;
        sscanf_s(buffer, "%1d", &number);

        char destination[MAX_CHAR_LEN] = "";
        int weight = 0;
        switch (number)
        {
        case 1:
            promptCountry(destination);
            printBST(GET_BST(hashTable, destination));
            continue;
        case 2:
            promptCountry(destination);
            promptWeight(&weight);
            printf("Parcels lower than %d \n", weight);
            printBSTLower(GET_BST(hashTable, destination), weight);
            putchar('\n');
            printf("Parcels higher than %d \n", weight);
            printBSTHigher(GET_BST(hashTable, destination), weight);
            putchar('\n');
            continue;
        case 3:
            promptCountry(destination);
            printf("Total load: %d gm\n", overallWeight(GET_BST(hashTable, destination)));
            printf("Total valuation: $%.2f\n", overallValue(GET_BST(hashTable, destination)));
            putchar('\n');
            continue;
        case 4:
            promptCountry(destination);
            printf("Cheapest parcel detail:\n");
            printParcel(cheapest(GET_BST(hashTable, destination)));
            putchar('\n');
            printf("Most expensive parcel detail:\n");
            printParcel(mostExpensive(GET_BST(hashTable, destination)));
            putchar('\n');
            continue;
        case 5:
            promptCountry(destination);
            printf("Lightest parcel detail:\n");
            printParcel(lightest(GET_BST(hashTable, destination)));
            putchar('\n');
            printf("Heaviest parcel detail:\n");
            printParcel(heaviest(GET_BST(hashTable, destination)));
            putchar('\n');
            continue;
        case 6:
            printf("Exit Application.\n");
            break;
        default:
            printf("Please enter a number in range of 1 - 6!\n");
            continue;
        }

        for (size_t i = 0; i < BUCKETS_SIZE; ++i)
        {
            freeBST(hashTable[i]);
        }
        break;
    }

    return 0;
}

/*
 * Function : hash
 * Description :
 *   Generates a hash value for a given string using the djb2 algorithm.
 * Parameters :
 *   unsigned char* str - The string to be hashed
 * Return : unsigned long - The computed hash value
 */
unsigned long hash(unsigned char* str) 
{
    unsigned long hash = 5381;
    int c = 0;
    while ((c = *str++) != '\0') 
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/*
 * Function : promptCountry
 * Description :
 *   Prompts the user to enter a country name and stores it in the output buffer.
 * Parameters :
 *   char* output - Buffer to store the entered country name
 * Return : void
 */
void promptCountry(char* output)
{
    printf("Country: ");
    char buffer[BUFSIZ] = "";
    fgets(buffer, BUFSIZ, stdin);
    sscanf_s(buffer, "%[^\n]s", output, MAX_CHAR_LEN);
    putchar('\n');
}

/*
 * Function : promptWeight
 * Description :
 *   Prompts the user to enter a weight and stores it in the output variable.
 * Parameters :
 *   int* output - Pointer to store the entered weight
 * Return : void
 */
void promptWeight(int* output)
{
    char buffer[BUFSIZ] = "";
    printf("Weight: ");
    fgets(buffer, BUFSIZ, stdin);
    sscanf_s(buffer, "%d", output);
    putchar('\n');
}

/*
 * Function : printParcel
 * Description :
 *   Prints the details of a single parcel.
 * Parameters :
 *   const Parcel* node - Pointer to the parcel to be printed
 * Return : void
 */
void printParcel(const Parcel* node)
{
    printf("Destination: %s\n", node->destination);
    printf("Weight: %d gms\n", node->weight);
    printf("Value: $%.2f\n", node->value);
    putchar('\n');
}

/*
 * Function : insertBST
 * Description :
 *   Inserts a new parcel into the Binary Search Tree.
 * Parameters :
 *   Parcel* node - The current node in the BST
 *   const char* destination - Destination of the parcel
 *   int weight - Weight of the parcel
 *   float value - Value of the parcel
 * Return : Parcel* - Pointer to the root of the updated BST
 */
Parcel* insertBST(Parcel* node, const char* destination, int weight, float value)
{
    if (node == NULL)
    {
        node = static_cast<Parcel*>(malloc(sizeof(Parcel)));
        CHECK_ALLOC(node == NULL);
        node->destination = static_cast<char*>(malloc(strlen(destination) + 1));
        CHECK_ALLOC(node->destination == NULL);
        strcpy_s(node->destination, strlen(destination) + 1, destination);
        node->weight = weight;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (node->weight > weight)
        node->left = insertBST(node->left, destination, weight, value);
    else if (node->weight < weight)
        node->right = insertBST(node->right, destination, weight, value);
    return node;
}

/*
 * Function : freeBST
 * Description :
 *   Frees the memory allocated for the entire Binary Search Tree.
 * Parameters :
 *   Parcel* node - The root of the BST to be freed
 * Return : void
 */
void freeBST(Parcel* node)
{
    if (node == NULL) return;

    freeBST(node->left);
    freeBST(node->right);
    free(node->destination);
    free(node);
}

/*
 * Function : printBST
 * Description :
 *   Prints all parcels in the Binary Search Tree in-order (sorted by weight).
 * Parameters :
 *   const Parcel* node - The root of the BST to be printed
 * Return : void
 */
void printBST(const Parcel* node)
{
    if (node == NULL) return;

    printBST(node->left);
    printParcel(node);
    printBST(node->right);
}

/*
 * Function : printBSTHigher
 * Description :
 *   Prints all parcels in the BST with weight higher than the specified weight.
 * Parameters :
 *   const Parcel* node - The root of the BST
 *   int weight - The weight threshold
 * Return : void
 */
void printBSTHigher(const Parcel* node, int weight)
{
    if (node == NULL) return;

    printBSTHigher(node->left, weight);
    if (node->weight > weight)
        printParcel(node);
    printBSTHigher(node->right, weight);
}

/*
 * Function : printBSTLower
 * Description :
 *   Prints all parcels in the BST with weight lower than the specified weight.
 * Parameters :
 *   const Parcel* node - The root of the BST
 *   int weight - The weight threshold
 * Return : void
 */
void printBSTLower(const Parcel* node, int weight)
{
    if (node == NULL) return;

    printBSTLower(node->left, weight);
    if (node->weight < weight)
        printParcel(node);
    printBSTLower(node->right, weight);
}

/*
 * Function : overallWeight
 * Description :
 *   Calculates the total weight of all parcels in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : int - The total weight of all parcels
 */
int overallWeight(const Parcel* node)
{
    if (node == NULL) return 0;
    return overallWeight(node->left) + overallWeight(node->right) + node->weight;
}

/*
 * Function : overallValue
 * Description :
 *   Calculates the total value of all parcels in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : float - The total value of all parcels
 */
float overallValue(const Parcel* node)
{
    if (node == NULL) return 0.0f;
    return overallValue(node->left) + overallValue(node->right) + node->value;
}

/*
 * Function : cheapest
 * Description :
 *   Finds the parcel with the lowest value in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : const Parcel* - Pointer to the cheapest parcel
 */
const Parcel* cheapest(const Parcel* node)
{
    if (node == NULL) return NULL;
 
    const Parcel* left = cheapest(node->left);
    const Parcel* right = cheapest(node->right);
    const Parcel* cheapest = node;
    if (left) cheapest = left->value < cheapest->value ? left : cheapest;
    if (right) cheapest = right->value < cheapest->value ? right : cheapest;
    return cheapest;
}

/*
 * Function : mostExpensive
 * Description :
 *   Finds the parcel with the highest value in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : const Parcel* - Pointer to the most expensive parcel
 */
const Parcel* mostExpensive(const Parcel* node)
{
    if (node == NULL) return NULL;

    const Parcel* left = mostExpensive(node->left);
    const Parcel* right = mostExpensive(node->right);
    const Parcel* mostExpensive = node;
    if (left) mostExpensive = left->value > mostExpensive->value ? left : mostExpensive;
    if (right) mostExpensive = right->value > mostExpensive->value ? right : mostExpensive;
    return mostExpensive;
}

/*
 * Function : lightest
 * Description :
 *   Finds the parcel with the lowest weight in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : const Parcel* - Pointer to the lightest parcel
 */
const Parcel* lightest(const Parcel* node)
{
    if (node->left == NULL) return node;
    return lightest(node->left);
}

/*
 * Function : heaviest
 * Description :
 *   Finds the parcel with the highest weight in the BST.
 * Parameters :
 *   const Parcel* node - The root of the BST
 * Return : const Parcel* - Pointer to the heaviest parcel
 */
const Parcel* heaviest(const Parcel* node)
{
    if (node->right == NULL) return node;
    return heaviest(node->right);
}