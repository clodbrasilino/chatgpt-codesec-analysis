#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    long value;
} Counter;

static int compare_counters(const void *left, const void *right)
{
    const Counter *a = left;
    const Counter *b = right;

    if (a->value < b->value) {
        return 1;
    }
    if (a->value > b->value) {
        return -1;
    }
    return strcmp(a->key, b->key);
}

static void sort_counters_by_value(Counter *counters, size_t count)
{
    if (counters != NULL && count > 1U) {
        qsort(counters, count, sizeof(*counters), compare_counters);
    }
}

int main(void)
{
    Counter counters[] = {
        {"apple", 4},
        {"orange", 2},
        {"banana", 7},
        {"pear", 4}
    };
    const size_t count = sizeof(counters) / sizeof(counters[0]);

    sort_counters_by_value(counters, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s: %ld\n", counters[i].key, counters[i].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}