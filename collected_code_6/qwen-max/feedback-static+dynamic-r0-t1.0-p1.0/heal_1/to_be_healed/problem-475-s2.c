#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Counter;

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'counterA' can be declared as pointer to const [constVariablePointer]
     */
    Counter *counterA = (Counter *)a;
    /* Possible weaknesses found:
     *  Variable 'counterB' can be declared as pointer to const [constVariablePointer]
     */
    Counter *counterB = (Counter *)b;
    return counterB->value - counterA->value;
}

void sortCounterByValue(Counter *counters, int size) {
    qsort(counters, size, sizeof(Counter), compare);
}

int main() {
    Counter counters[] = {{1, 3}, {2, 7}, {3, 5}, {4, 1}};
    int size = sizeof(counters) / sizeof(Counter);

    sortCounterByValue(counters, size);

    for (int i = 0; i < size; ++i) {
        printf("Key: %d, Value: %d\n", counters[i].key, counters[i].value);
    }

    return 0;
}