#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} CounterModel;

int compareCounters(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'counterA' can be declared as pointer to const [constVariablePointer]
     */
    CounterModel *counterA = (CounterModel *)a;
    /* Possible weaknesses found:
     *  Variable 'counterB' can be declared as pointer to const [constVariablePointer]
     */
    CounterModel *counterB = (CounterModel *)b;
    return (counterA->value - counterB->value);
}

void sortCounters(CounterModel **counters, int size) {
    if (counters == NULL || *counters == NULL || size <= 0) {
        return;
    }
    qsort(*counters, size, sizeof(CounterModel), compareCounters);
}

void freeCounters(CounterModel *counters, int size) {
    if (counters == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        free(counters[i].key);
    }
    free(counters);
}

int main() {
    int size = 5;
    CounterModel *counters = (CounterModel *)malloc(size * sizeof(CounterModel));
    
    if (counters == NULL) {
        return 1;
    }

    const char* keys[] = {"apple", "banana", "orange", "grape", "melon"};
    const int values[] = {5, 2, 8, 1, 4};

    for (int i = 0; i < size; i++) {
        counters[i].key = (char *)malloc(strlen(keys[i]) + 1);
        if (counters[i].key == NULL) {
            freeCounters(counters, i);
            return 1;
        }
        strcpy(counters[i].key, keys[i]);
        counters[i].value = values[i];
    }

    sortCounters(&counters, size);

    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    freeCounters(counters, size);

    return 0;
}