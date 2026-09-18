#include <stdio.h>
#include <stdlib.h>

// Struct for sublist
typedef struct {
    int first;
    int second;
} sublist;

// Compare function for the second element of the sublist
int compare(const void *a, const void *b) {
    sublist *subListA = (sublist *)a;
    sublist *subListB = (sublist *)b;
    return subListA->second - subListB->second;
}

// Function to print array
void printArray(sublist arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d, %d\n", arr[i].first, arr[i].second);
}

int main() {
    sublist arr[] = { {11, 11}, {2, 2}, {33, 33}, {4, 4} };
    int size = sizeof(arr) / sizeof(arr[0]);

    // Sort according to second element in sublist
    qsort(arr, size, sizeof(sublist), compare);

    // print sorted array
    printArray(arr, size);

    return 0;
}