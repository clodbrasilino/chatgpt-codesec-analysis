#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if an element is present in an array
bool isPresent(int array[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
}

// Function to find the distinct elements
int distinctElements(int array[], int size) {
    int distinct[size];
    int distinct_count = 0;

    for (int i = 0; i < size; i++) {
        if (!isPresent(distinct, distinct_count, array[i])) {
            distinct[distinct_count++] = array[i];
        }
    }
    return distinct_count;
}

int main() {
    int array[] = {1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);

    int result = distinctElements(array, size);

    printf("Minimum number of subsets with distinct elements: %d\n", result);

    return 0;
}