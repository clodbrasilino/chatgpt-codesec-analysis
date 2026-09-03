#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} FrequencyTuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    int cmpFirst = strcmp(tupleA->first, tupleB->first);
    if (cmpFirst != 0) return cmpFirst;
    return strcmp(tupleA->second, tupleB->second);
}

FrequencyTuple* assign_frequencies(Tuple *tuples, int count) {
    qsort(tuples, count, sizeof(Tuple), compare_tuples);

    FrequencyTuple *freqTuples = (FrequencyTuple *)malloc(count * sizeof(FrequencyTuple));
    if (freqTuples == NULL) {
        return NULL;
    }

    int freqIndex = 0;
    for (int i = 0; i < count; ++i) {
        if (i == 0 || (strcmp(tuples[i].first, tuples[i-1].first) != 0 || strcmp(tuples[i].second, tuples[i-1].second) != 0)) {
            freqTuples[freqIndex].tuple = tuples[i];
            freqTuples[freqIndex].frequency = 1;
            freqIndex++;
        } else {
            freqTuples[freqIndex - 1].frequency++;
        }
    }

    FrequencyTuple *result = (FrequencyTuple *)realloc(freqTuples, freqIndex * sizeof(FrequencyTuple));
    if (result == NULL) {
        free(freqTuples);
        return NULL;
    }

    return result;
}

int main() {
    Tuple tuples[] = {
        {"apple", "banana"},
        {"apple", "banana"},
        {"orange", "grape"},
        {"apple", "orange"},
        {"orange", "grape"}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);

    FrequencyTuple *freqTuples = assign_frequencies(tuples, count);
    if (freqTuples == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  outer condition: i<count
     */
    for (int i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
         *  opposite inner condition: i>=count
         */
        if (i >= count) break;
        /* Possible weaknesses found:
         * ASan: heap-buffer-overflow
         */
        if (freqTuples[i].frequency > 0) {
            printf("(%s, %s): %d\n", freqTuples[i].tuple.first, freqTuples[i].tuple.second, freqTuples[i].frequency);
        }
    }

    free(freqTuples);
    return 0;
}