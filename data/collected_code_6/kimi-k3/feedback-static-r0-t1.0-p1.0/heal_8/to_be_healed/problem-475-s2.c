#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LENGTH];
    int value;
} Counter;

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    return (ca->value > cb->value) - (ca->value < cb->value);
}

int sort_counter_by_value(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
    return 0;
}

int set_counter_key(Counter *counter, const char *key) {
    if (counter == NULL || key == NULL) {
        return -1;
    }
    size_t len = strnlen(key, MAX_KEY_LENGTH);
    if (len >= MAX_KEY_LENGTH) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(counter->key, key, len + 1);
    return 0;
}

int main(void) {
    Counter counters[5];
    const char *keys[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const int values[] = {5, 2, 9, 1, 7};
    size_t count = sizeof(counters) / sizeof(counters[0]);

    for (size_t i = 0; i < count; i++) {
        if (set_counter_key(&counters[i], keys[i]) != 0) {
            fprintf(stderr, "Error: key too long\n");
            return EXIT_FAILURE;
        }
        counters[i].value = values[i];
    }

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Error: failed to sort counters\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    return EXIT_SUCCESS;
}