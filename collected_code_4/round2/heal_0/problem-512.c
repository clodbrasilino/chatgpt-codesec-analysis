#include <stdio.h>

#define SIZE 10

// Define structure (tuple) to hold two elements
struct Tuple {
    int a;
    int b;
};

// Function to count frequency
int countFrequency(struct Tuple arr[], int num) {
    int count = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (arr[i].a == num || arr[i].b == num) {
            count++;
        }
    }
    return count;
}

// Main function
int main(void) {
    struct Tuple arr[SIZE] = {{1, 2}, {3, 4}, {5, 2}, {1, 6}, {7, 4}, {1, 8}, {3, 1}, {9, 4}, {1, 2}, {5, 2}};

    int num = 1;
    printf("Frequency of %d is %d\n", num, countFrequency(arr, num));

    return 0;
}