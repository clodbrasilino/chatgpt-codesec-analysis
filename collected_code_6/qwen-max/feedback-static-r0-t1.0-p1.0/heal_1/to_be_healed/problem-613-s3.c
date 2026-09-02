#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Record::id' is never used. [unusedStructMember]
     */
    int id;
    int value;
} Record;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::key' is never used. [unusedStructMember]
     */
    int key;
    Record *records;
    int count;
} Tuple;

int findMaxValue(Tuple *tuples, int tupleCount) {
    if (tupleCount <= 0) return INT_MIN;

    int max = INT_MIN;
    for (int i = 0; i < tupleCount; ++i) {
        for (int j = 0; j < tuples[i].count; ++j) {
            if (tuples[i].records[j].value > max) {
                max = tuples[i].records[j].value;
            }
        }
    }
    return max;
}

int main() {
    Tuple tuples[] = {
        {1, (Record[]){ {10, 20}, {30, 40} }, 2},
        {2, (Record[]){ {5, 15}, {25, 35} }, 2},
        {3, (Record[]){ {100, 200}, {300, 400} }, 2}
    };
    int tupleCount = sizeof(tuples) / sizeof(tuples[0]);

    int maxValue = findMaxValue(tuples, tupleCount);
    printf("Maximum value: %d\n", maxValue);

    return 0;
}