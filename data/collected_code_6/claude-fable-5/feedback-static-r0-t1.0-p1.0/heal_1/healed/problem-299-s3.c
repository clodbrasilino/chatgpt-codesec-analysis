#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 64
#define MAX_ENTRIES 128

typedef struct {
    char name[MAX_NAME_LEN];
    int score;
} Tuple;

typedef struct {
    char name[MAX_NAME_LEN];
    int total;
} Aggregate;

static int find_aggregate(const Aggregate *aggs, size_t count, const char *name)
{
    size_t i;

    if (aggs == NULL || name == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (strncmp(aggs[i].name, name, MAX_NAME_LEN) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static int max_aggregate(const Tuple *tuples, size_t count, Aggregate *result)
{
    Aggregate aggs[MAX_ENTRIES];
    size_t agg_count = 0;
    size_t i;
    size_t max_index = 0;

    if (tuples == NULL || result == NULL || count == 0 || count > MAX_ENTRIES) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        int idx = find_aggregate(aggs, agg_count, tuples[i].name);
        if (idx >= 0) {
            aggs[idx].total += tuples[i].score;
        } else {
            int written;

            if (agg_count >= MAX_ENTRIES) {
                return -1;
            }
            written = snprintf(aggs[agg_count].name, sizeof(aggs[agg_count].name),
                               "%s", tuples[i].name);
            if (written < 0 || (size_t)written >= sizeof(aggs[agg_count].name)) {
                return -1;
            }
            aggs[agg_count].total = tuples[i].score;
            agg_count++;
        }
    }

    for (i = 1; i < agg_count; i++) {
        if (aggs[i].total > aggs[max_index].total) {
            max_index = i;
        }
    }

    {
        int written = snprintf(result->name, sizeof(result->name), "%s",
                               aggs[max_index].name);
        if (written < 0 || (size_t)written >= sizeof(result->name)) {
            return -1;
        }
    }
    result->total = aggs[max_index].total;

    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {"Juan Whelan", 90},
        {"Sabah Colley", 88},
        {"Peter Nichols", 7},
        {"Juan Whelan", 122},
        {"Sabah Colley", 84}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Aggregate result;

    if (max_aggregate(tuples, count, &result) != 0) {
        fprintf(stderr, "Failed to compute maximum aggregate\n");
        return EXIT_FAILURE;
    }

    if (printf("(%s, %d)\n", result.name, result.total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}