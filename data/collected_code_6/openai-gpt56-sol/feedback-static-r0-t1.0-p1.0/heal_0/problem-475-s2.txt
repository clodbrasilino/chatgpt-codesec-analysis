#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    long long value;
} Counter;

static int compare_counters(const void *lhs, const void *rhs)
{
    const Counter *a = lhs;
    const Counter *b = rhs;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return strcmp(a->name, b->name);
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
        {"requests", 42},
        {"errors", 3},
        {"successes", 39},
        {"retries", 7}
    };
    const size_t count = sizeof(counters) / sizeof(counters[0]);

    sort_counters_by_value(counters, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s: %lld\n", counters[i].name, counters[i].value) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}