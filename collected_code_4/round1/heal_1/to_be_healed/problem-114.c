#include<stdio.h>
#include<stdlib.h>

typedef struct tuple {
    int number1;
    int number2;
} Tuple;

typedef struct freqTuple {
    Tuple tuple;
    int frequency;
} FreqTuple;

FreqTuple* getTupleFrequency(Tuple* tupleList, int size, int* freqSize) {
    FreqTuple* freqTupleList = (FreqTuple*)malloc(sizeof(FreqTuple)*size);

    if (freqTupleList == NULL) {
        *freqSize = 0;
        return NULL;
    }

    int freqTupleListSize = 0;

    for (int i = 0; i < size; i++) {
        int j;
        for (j = 0; j < freqTupleListSize; j++) {
            if (freqTupleList[j].tuple.number1 == tupleList[i].number1 &&
                freqTupleList[j].tuple.number2 == tupleList[i].number2) {
                freqTupleList[j].frequency++;
                break;
            }
        }

        if (j == freqTupleListSize) {
            freqTupleList[freqTupleListSize].tuple = tupleList[i];
            freqTupleList[freqTupleListSize].frequency = 1;
            freqTupleListSize++;
        }
    }

    *freqSize = freqTupleListSize;
    freqTupleList = (FreqTuple*)realloc(freqTupleList, sizeof(FreqTuple)*freqTupleListSize);

    /* Possible weaknesses found:
     *  leak of 'freqTupleList' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return freqTupleList;
}

int main() {
    Tuple tupleList[] = { {1, 2}, {1, 2}, {1, 2}, {2, 3}, {2, 3}, {3, 4} };
    int freqSize;

    FreqTuple* freqTupleList = getTupleFrequency(tupleList, 6, &freqSize);

    if (freqTupleList == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    for (int i = 0; i < freqSize; i++) {
        printf("Tuple: %d, %d. Frequency: %d\n", freqTupleList[i].tuple.number1,
               freqTupleList[i].tuple.number2, freqTupleList[i].frequency);
    }

    free(freqTupleList);
    
    return 0;
}