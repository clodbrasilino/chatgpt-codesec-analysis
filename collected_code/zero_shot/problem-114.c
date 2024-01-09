#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Tuple {
    int value1;
    int value2;
} Tuple;

void assignFrequency(Tuple tupleList[], int size) {
    int i, j, count;
    int frequency[size];
    
    for (i = 0; i < size; i++) {
        // Initialize frequency array
        frequency[i] = -1;
    }
    
    for (i = 0; i < size; i++) {
        count = 1;
        
        for (j = i + 1; j < size; j++) {
            if (tupleList[i].value1 == tupleList[j].value1 && tupleList[i].value2 == tupleList[j].value2) {
                count++;
                // Make sure the tuples with the same values are not counted again
                frequency[j] = 0;
            }
        }
        
        if (frequency[i] != 0) {
            frequency[i] = count;
        }
    }
    
    // Print frequency of each tuple
    for (i = 0; i < size; i++) {
        if (frequency[i] != 0) {
            printf("Tuple (%d, %d) occurs %d times\n", tupleList[i].value1, tupleList[i].value2, frequency[i]);
        }
    }
}

int main() {
    int size;
    Tuple tupleList[MAX_SIZE];
    
    printf("Enter the number of tuples: ");
    scanf("%d", &size);
    
    if (size > MAX_SIZE) {
        printf("Exceeded maximum size\n");
        return 0;
    }
    
    printf("Enter the tuples:\n");
    for (int i = 0; i < size; i++) {
        printf("Tuple %d:\n", i + 1);
        printf("Value 1: ");
        scanf("%d", &tupleList[i].value1);
        printf("Value 2: ");
        scanf("%d", &tupleList[i].value2);
    }
    
    assignFrequency(tupleList, size);
    
    return 0;
}