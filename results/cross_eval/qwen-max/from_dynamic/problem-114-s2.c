#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple t;
    int frequency;
} FrequencyTuple;

FrequencyTuple* assignFrequencies(Tuple* tuples, int n, int* returnSize) {
    FrequencyTuple* fTuples = (FrequencyTuple*)malloc(n * sizeof(FrequencyTuple));
    for (int i = 0; i < n; ++i) {
        fTuples[i].t = tuples[i];
        fTuples[i].frequency = 1;
        for (int j = 0; j < i; ++j) {
            if (fTuples[j].t.first == tuples[i].first && fTuples[j].t.second == tuples[i].second) {
                fTuples[j].frequency++;
                fTuples[i].frequency = 0;
                break;
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (fTuples[i].frequency > 0) {
            fTuples[count++] = fTuples[i];
        }
    }

    *returnSize = count;
    FrequencyTuple* result = (FrequencyTuple*)realloc(fTuples, count * sizeof(FrequencyTuple));
    return result;
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 3}, {1, 2}, {3, 4}, {1, 2}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int returnSize;
    FrequencyTuple* fTuples = assignFrequencies(tuples, n, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("(%d, %d) -> %d\n", fTuples[i].t.first, fTuples[i].t.second, fTuples[i].frequency);
    }

    free(fTuples);
    return 0;
}