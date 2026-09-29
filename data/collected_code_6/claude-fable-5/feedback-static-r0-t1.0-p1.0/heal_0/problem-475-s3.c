#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int value;
} Counter;

static int compare_by_value(const void *a, const void *b)
{
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;

    if (ca->value < cb->value) {
        return 1;
    }
    if (ca->value > cb->value) {
        return -1;
    }
    return strcmp(ca->key, cb->key);
}

static int sort_counter_by_value(Counter *counters, size_t count)
{
    if (counters == NULL || count == 0U) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_by_value);
    return 0;
}

int main(void)
{
    size_t count = 5U;
    size_t i;
    Counter *counters = malloc(count * sizeof(Counter));

    if (counters == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    strncpy(counters[0].key, "apple", sizeof(counters[0].key) - 1U);
    counters[0].key[sizeof(counters[0].key) - 1U] = '\0';
    counters[0].value = 3;

    strncpy(counters[1].key, "banana", sizeof(counters[1].key) - 1U);
    counters[1].key[sizeof(counters[1].key) - 1U] = '\0';
    counters[1].value = 7;

    strncpy(counters[2].key, "cherry", sizeof(counters[2].key) - 1U);
    counters[2].key[sizeof(counters[2].key) - 1U] = '\0';
    counters[2].value = 1;

    strncpy(counters[3].key, "date", sizeof(counters[3].key) - 1U);
    counters[3].key[sizeof(counters[3].key) - 1U] = '\0';
    counters[3].value = 7;

    strncpy(counters[4].key, "elderberry", sizeof(counters[4].key) - 1U);
    counters[4].key[sizeof(counters[4].key) - 1U] = '\0';
    counters[4].value = 5;

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(counters);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("%s: %d\n", counters[i].key, counters[i].value) < 0) {
            fprintf(stderr, "Output failed\n");
            free(counters);
            return EXIT_FAILURE;
        }
    }

    free(counters);
    return EXIT_SUCCESS;
}