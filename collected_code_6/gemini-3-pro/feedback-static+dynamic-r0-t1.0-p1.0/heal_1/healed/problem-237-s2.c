#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int id;
};

struct OccurrenceFrequency {
    int count;
    int frequency;
};

void checkOccurrences(struct Tuple* tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return;
    }

    int maxId = 0;
    for (int i = 0; i < size; ++i) {
        if (tuples[i].id > maxId) {
            maxId = tuples[i].id;
        }
    }

    int* idCounts = (int*)calloc(maxId + 1, sizeof(int));
    if (idCounts == NULL) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        idCounts[tuples[i].id]++;
    }

    struct OccurrenceFrequency* freqList = (struct OccurrenceFrequency*)malloc((size + 1) * sizeof(struct OccurrenceFrequency));
    if (freqList == NULL) {
        free(idCounts);
        return;
    }

    for (int i = 0; i <= size; ++i) {
        freqList[i].count = i;
        freqList[i].frequency = 0;
    }

    for (int i = 0; i <= maxId; ++i) {
        if (idCounts[i] > 0) {
            freqList[idCounts[i]].frequency++;
        }
    }

    for (int i = 0; i <= size; ++i) {
        if (freqList[i].frequency > 0) {
            printf("Records occurring %d times: %d\n", freqList[i].count, freqList[i].frequency);
        }
    }

    free(idCounts);
    free(freqList);
}

int main(void) {
    struct Tuple tuples[] = {
        {1}, {2}, {1}, {3}, 
        {2}, {4}, {1}, {5}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    checkOccurrences(tuples, size);

    return 0;
}