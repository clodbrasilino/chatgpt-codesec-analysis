#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

void findFrequency(int **listOfLists, int numLists, const int *sizes, Frequency **frequencies, int *numFrequencies) {
    int i, j, k;
    int capacity = 10;
    *numFrequencies = 0;
    *frequencies = (Frequency *)malloc(capacity * sizeof(Frequency));
    if (*frequencies == NULL) {
        return;
    }

    for (i = 0; i < numLists; i++) {
        for (j = 0; j < sizes[i]; j++) {
            int value = listOfLists[i][j];
            int found = 0;
            for (k = 0; k < *numFrequencies; k++) {
                if ((*frequencies)[k].value == value) {
                    (*frequencies)[k].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                if (*numFrequencies >= capacity) {
                    capacity *= 2;
                    Frequency *newFrequencies = (Frequency *)realloc(*frequencies, capacity * sizeof(Frequency));
                    if (newFrequencies == NULL) {
                        free(*frequencies);
                        *frequencies = NULL;
                        return;
                    }
                    *frequencies = newFrequencies;
                }
                (*frequencies)[*numFrequencies].value = value;
                (*frequencies)[*numFrequencies].count = 1;
                (*numFrequencies)++;
            }
        }
    }
}

int main() {
    int i, j;
    int numLists = 3;
    int sizes[] = {3, 4, 2};
    int **listOfLists = (int **)malloc(numLists * sizeof(int *));
    if (listOfLists == NULL) {
        return 1;
    }

    for (i = 0; i < numLists; i++) {
        listOfLists[i] = (int *)malloc(sizes[i] * sizeof(int));
        if (listOfLists[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(listOfLists[j]);
            }
            free(listOfLists);
            return 1;
        }
    }

    listOfLists[0][0] = 1;
    listOfLists[0][1] = 2;
    listOfLists[0][2] = 3;

    listOfLists[1][0] = 2;
    listOfLists[1][1] = 3;
    listOfLists[1][2] = 4;
    listOfLists[1][3] = 5;

    listOfLists[2][0] = 1;
    listOfLists[2][1] = 2;

    Frequency *frequencies = NULL;
    int numFrequencies = 0;

    findFrequency(listOfLists, numLists, sizes, &frequencies, &numFrequencies);

    if (frequencies != NULL) {
        printf("Element frequencies:\n");
        for (i = 0; i < numFrequencies; i++) {
            printf("%d: %d\n", frequencies[i].value, frequencies[i].count);
        }
        free(frequencies);
    }

    for (i = 0; i < numLists; i++) {
        free(listOfLists[i]);
    }
    free(listOfLists);

    return 0;
}