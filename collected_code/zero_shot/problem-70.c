#include <stdio.h>

// Function to find whether all the given tuples have equal length or not
int checkTupleLength(int tuples[][2], int numTuples) {
    int i;
    int length = sizeof(tuples[0])/sizeof(tuples[0][0]);

    // Iterate through all tuples
    for (i = 1; i < numTuples; i++) {
        if (sizeof(tuples[i])/sizeof(tuples[i][0]) != length) {
            return 0; // Return false if a tuple has different length
        }
    }

    return 1; // Return true if all tuples have equal length
}

// Example usage
int main() {
    int tuples[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int numTuples = sizeof(tuples)/sizeof(tuples[0]);

    if (checkTupleLength(tuples, numTuples)) {
        printf("All tuples have equal length\n");
    } else {
        printf("Tuples have different lengths\n");
    }

    return 0;
}
