#include <stdio.h>

#define MAX_ELEMENTS 100

void findFrequency(const int lists[MAX_ELEMENTS][MAX_ELEMENTS], int numLists, int numElements) {
    int frequency[MAX_ELEMENTS] = {0};

    for (int i = 0; i < numLists; i++) {
        for (int j = 0; j < numElements; j++) {
            frequency[lists[i][j]]++;
        }
    }

    for (int i = 0; i < numElements; i++) {
        printf("Element %d: Frequency = %d\n", i, frequency[i]);
    }
}

int main() {
    int lists[MAX_ELEMENTS][MAX_ELEMENTS] = {{1, 2, 3}, {2, 3, 4}, {1, 3, 5}};
    int numLists = 3;
    int numElements = 3;

    findFrequency(lists, numLists, numElements);

    return 0;
}