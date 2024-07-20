#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SIZE 20

typedef struct ThesaurausKeyValuePair {
    char* Word;
    char* Synonym;
    struct ThesaurausKeyValuePair* NextKeyValuePair;
} ThesaurausKeyValuePair;

typedef struct Thesaurus {
    ThesaurausKeyValuePair* Table[SIZE];
} Thesaurus;


//prototypes
int GenerateHash(char* word);
ThesaurausKeyValuePair* InitializeKeyValuePair(char* word, char* synonym);
Thesaurus* InitializeHashTable(void);
void InsertWithSeparateChaining(Thesaurus* hashTable, char* word, char* synonym);
char* SearchWithSeparateChaining(Thesaurus* hashTable, char* word);

int main(int argc, const char* argv[]) {
    Thesaurus* thesauraus = InitializeHashTable();

    InsertWithSeparateChaining(thesauraus, "Bad", "Evil");
    InsertWithSeparateChaining(thesauraus, "Dab", "Pat");
    InsertWithSeparateChaining(thesauraus, "Cab", "Taxi");
    InsertWithSeparateChaining(thesauraus, "Ace", "Star");

    printf("Synonym for Bad is: %s\n", SearchWithSeparateChaining(thesauraus, "Bad"));
    printf("Synonym for Dab is: %s\n", SearchWithSeparateChaining(thesauraus, "Dab"));
    printf("Synonym for Cab is: %s\n", SearchWithSeparateChaining(thesauraus, "Cab"));
    printf("Synonym for Star is: %s\n", SearchWithSeparateChaining(thesauraus, "Star"));

   return 0;
}

int GenerateHash(char* word){
    int hash = 0;
    for (int i=0; word[i] != '\0'; i++) {
        int asciiValue = word[i];
        hash = (hash + asciiValue) % SIZE;
    }
    return hash;
}

ThesaurausKeyValuePair* InitializeKeyValuePair(char* word, char* synonym){
    ThesaurausKeyValuePair* kvp = (ThesaurausKeyValuePair*)malloc(sizeof(ThesaurausKeyValuePair));
    if(kvp == NULL){
        printf("EOM");
        exit(EXIT_FAILURE);
    }   
    
    kvp->Word = (char*)malloc(strlen(word));
    kvp->Word = word;
    kvp->Synonym = (char*)malloc(strlen(synonym));
    kvp->Synonym = synonym;
    kvp->NextKeyValuePair = NULL;
    return kvp;
}

Thesaurus* InitializeHashTable(void){
    Thesaurus* hashTable = (Thesaurus*)malloc(sizeof(Thesaurus));
    if(hashTable == NULL){
        printf("EOM");
        exit(EXIT_FAILURE);
    }
    
    for (int i=0; i<SIZE; i++) {
        hashTable->Table[i] = NULL;
    }
    
    return hashTable;
}

void InsertWithSeparateChaining(Thesaurus* hashTable, char* word, char* synonym){
    // GENERATE HASH
    int hash = GenerateHash(word);
    
    // INITIALIZE KEY VALUE PAIR
    ThesaurausKeyValuePair* kvp = InitializeKeyValuePair(word, synonym);
    
    if(hashTable->Table[hash] == NULL){ // this means there arent any collisions
        hashTable->Table[hash] = kvp;
        return;
    }
    
    // This means there is a collision, add the kvp to the end of the linked list.
    ThesaurausKeyValuePair* current = hashTable->Table[hash];
    while(current->NextKeyValuePair != NULL){
        current = current->NextKeyValuePair;
    }
    
    current->NextKeyValuePair = kvp;
}

char* SearchWithSeparateChaining(Thesaurus* hashTable, char* word){
    int hash = GenerateHash(word);
    
    if(hashTable->Table[hash] == NULL){
        return "ERROR: Cannot find the word!";
    }
    
    
    ThesaurausKeyValuePair* current = hashTable->Table[hash];
    
    /*if(current->NextKeyValuePair == NULL && strcmp(current->Word, word) == 0){
        return current->Synonym;
    }*/
    
    while(current != NULL){
        if(strcmp(current->Word, word) == 0){
            return current->Synonym;
        }
        
        current = current->NextKeyValuePair;
    }
    
    return "ERROR: Cannot find the word!";
}




