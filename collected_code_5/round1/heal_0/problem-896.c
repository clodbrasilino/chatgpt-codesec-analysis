#include <stdio.h>
#include <stdlib.h>

// A structure to represent a tuple
struct Tuple {
    int data[2]; // Assume tuple contains two integers
};

// Function to compare two tuples (used in qsort)
int compareTuples(const void *a, const void *b) {
    const struct Tuple *ta = (const struct Tuple *)a;
    const struct Tuple *tb = (const struct Tuple *)b;

    if (ta->data[1] > tb->data[1])
        return 1;
    if (ta->data[1] < tb->data[1])
        return -1;

    return 0;
}

// Function to print an array of tuples
void printArray(struct Tuple arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("(%d, %d) ", arr[i].data[0], arr[i].data[1]);
    printf("\n");
}

int main() {
    struct Tuple arr[] = { {1, 8}, {5, 3}, {2, 6}, {4, 2} };

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    // Use built-in qsort function
    qsort(arr, n, sizeof(struct Tuple), compareTuples);

    printf("Sorted array (by the last element in each tuple): \n");
    printArray(arr, n);

    return 0;
}
