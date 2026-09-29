#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    unsigned long count;
} Counter;

static int compare_counters(const void *lhs, const void *rhs)
{
    const Counter *a = lhs;
    const Counter *b = rhs;

    if (a->count < b->count) {
        return -1;
    }
    if (a->count > b->count) {
        return 1;
    }
    return 0;
}

static int sort_counters_by_value(Counter *counters, size_t count)
{
    if (counters == NULL && count != 0U) {
        errno = EINVAL;
        return -1;
    }

    if (count > 1U) {
        qsort(counters, count, sizeof(*counters), compare_counters);
    }

    return 0;
}

int main(void)
{
    Counter counters[] = {
        {"errors", 7UL},
        {"requests", 120UL},
        {"timeouts", 3UL},
        {"retries", 15UL}
    };
    const size_t count = sizeof(counters) / sizeof(counters[0]);

    if (sort_counters_by_value(counters, count) != 0) {
        perror("sort_counters_by_value");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s: %lu\n", counters[i].name, counters[i].count) < 0) {
            fputs("Output error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}