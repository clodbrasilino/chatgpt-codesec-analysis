#include <stdio.h>

// function to sort list of tuples in increasing order by the last element
void sortTuples(int list[][2], int n) {
    int i, j, temp;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-1-i; j++) {
            if (list[j][1] > list[j+1][1]) {
                // swap last elements
                temp = list[j][1];
                list[j][1] = list[j+1][1];
                list[j+1][1] = temp;
            }
        }
    }
}

int main() {
    // example list of tuples
    int tuples[][2] = {{1, 5}, {2, 3}, {3, 7}, {4, 1}, {5, 9}};
    int numTuples = sizeof(tuples)/sizeof(tuples[0]);

    // print original list of tuples
    printf("Original List of Tuples:\n");
    for (int i = 0; i < numTuples; i++) {
        printf("(%d, %d) ", tuples[i][0], tuples[i][1]);
    }
    printf("\n");

    // sort list of tuples
    sortTuples(tuples, numTuples);

    // print sorted list of tuples
    printf("Sorted List of Tuples:\n");
    for (int i = 0; i < numTuples; i++) {
        printf("(%d, %d) ", tuples[i][0], tuples[i][1]);
    }
    printf("\n");

    return 0;
}