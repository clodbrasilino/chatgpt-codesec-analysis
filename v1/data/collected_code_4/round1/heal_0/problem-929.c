#include <stdio.h>
#include <stdlib.h>

// Prototype of a structure to hold items
typedef struct Item {
    int value;
    int count;
} Item;

// Function to count occurrence of an integer in array
void countRepeated(int* arr, int size, Item* result) {
    // Initialize count of all Items as 0
    for (int i=0; i<size; i++)
        result[i].count = 0;

    // Traverse through array and count occurrences
    for(int i = 0; i < size; i++) {
        result[arr[i]].value = arr[i];
        result[arr[i]].count++;
    }
}

// The main function to count occurrence of all
// items in an array
int main() {
    int arr[] = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0, 7, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    //Initialize result struct
    Item *result = malloc(n * sizeof(Item));

    if(result != NULL) {
        countRepeated(arr, n, result);

        for (int i = 0; i < n; i++)
            printf("%d, %d \n", result[i].value, result[i].count);

        // Deallocate memory space after use
        free(result);
    }
    else {
        printf("Memory allocation failed.");
        return 1;
    }

    return 0;
}