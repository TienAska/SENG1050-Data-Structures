#include <stdio.h>

void InsertionSort(int input[], int size){
    for (int readIndex = 1; readIndex < size; readIndex++) {
        int value = input[readIndex];
        int j = readIndex - 1;
        
        while(j >= 0 && input[j] > value){
            input[j + 1] = input[j];
            j--;
        }
        
        input[j + 1] = value;
    }
}

void PrintArray(int input[], int size){
    for (int i = 0; i < size; i++) {
        printf("%d\n", input[i]);
    }
}

int main(int argc, const char * argv[]) {
    int input[6] = {3, 5, 1, 2, 4, 6};
    int size = sizeof(input)/sizeof(int);
    InsertionSort(input, size);
    PrintArray(input, size);
    return 0;
}
