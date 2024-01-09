#include <stdio.h>

// function to convert set into ordered tuples
void convertSetToTuples(int set[], int size) {
    // bubble sort to sort the set in ascending order
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (set[j] > set[j+1]) {
                // swap elements
                int temp = set[j];
                set[j] = set[j+1];
                set[j+1] = temp;
            }
        }
    }

    // print the ordered tuples
    for (int i = 0; i < size-2; i++) {
        for (int j = i+1; j < size-1; j++) {
            for (int k = j+1; k < size; k++) {
                printf("(%d, %d, %d)\n", set[i], set[j], set[k]);
            }
        }
    }
}

int main() {
    int set[] = {4, 2, 6, 1, 3};
    int size = sizeof(set) / sizeof(set[0]);
    
    convertSetToTuples(set, size);

    return 0;
}