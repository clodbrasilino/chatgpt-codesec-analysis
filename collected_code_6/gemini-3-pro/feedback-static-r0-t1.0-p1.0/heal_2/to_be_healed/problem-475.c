#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} CounterModel;

int compareCounters(const void *a, const void *b) {
    const CounterModel *counterA = (const CounterModel *)a;
    const CounterModel *counterB = (const CounterModel *)b;
    
    if (counterA->value < counterB->value) return -1;
    if (counterA->value > counterB->value) return 1;
    return 0;
}

void sortCounters(CounterModel **counters, int size) {
    if (counters == NULL || *counters == NULL || size <= 0) {
        return;
    }
    qsort(*counters, (size_t)size, sizeof(CounterModel), compareCounters);
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

int main(void) {
    int size = 5;
    CounterModel *counters = (CounterModel *)malloc((size_t)size * sizeof(CounterModel));
    
    if (counters == NULL) {
        return 1;
    }

    const char* keys[] = {"apple", "banana", "orange", "grape", "melon"};
    const int values[] = {5, 2, 8, 1, 4};

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(keys[i]);
        counters[i].key = (char *)malloc(len + 1);
        if (counters[i].key == NULL) {
            freeCounters(counters, i);
            return 1;
        }
        snprintf(counters[i].key, len + 1, "%s", keys[i]);
        counters[i].value = values[i];
    }

    sortCounters(&counters, size);

    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    freeCounters(counters, size);

    return 0;
}