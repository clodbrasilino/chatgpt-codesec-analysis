#include <stdio.h>

void rearrangeTuples(int tuples[], int orderedList[], int size) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[orderedList[i]] = tuples[i];
    }
    for (int i = 0; i < size; i++) {
        tuples[i] = temp[i];
    }
}

int main() {
    // Example usage
    int tuples[] = {1, 2, 3, 4};
    int orderedList[] = {2, 3, 1, 0};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    rearrangeTuples(tuples, orderedList, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", tuples[i]);
    }

    return 0;
}