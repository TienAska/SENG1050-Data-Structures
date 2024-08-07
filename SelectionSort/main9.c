#include <stdio.h>

void SelectionSort(int input[], int size){
    for (int readIndex = 0; readIndex < size - 1; readIndex++) {
        int leastValue = input[readIndex];
        int indexOfLeastValue = readIndex;
        
        //Helps find the least value in the array after i
        for (int j = readIndex + 1; j < size; j++) {
            if(leastValue >  input[j]){
                leastValue = input[j];
                indexOfLeastValue = j;
            }
        }
        
        if(indexOfLeastValue != readIndex){
            input[indexOfLeastValue] = input[readIndex];
            input[readIndex] = leastValue;
        }
    }
    
}

void PrintArray(int input[], int size){
    for (int i =0; i < size; i++) {
        printf("%d\n", input[i]);
    }
}

int main(int argc, const char * argv[]) {
    int input[6] = {3, 5, 2, 1, 4, 6};
    int size = sizeof(input)/sizeof(int);
    SelectionSort(input, size);
    PrintArray(input, size);
    return 0;
}
