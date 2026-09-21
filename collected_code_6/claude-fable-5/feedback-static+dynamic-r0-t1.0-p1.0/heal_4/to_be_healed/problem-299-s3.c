#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 64
#define MAX_ENTRIES 128

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    int score;
} Tuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

static int copy_name(char *dest, size_t dest_size, const char *src)
{
    int written;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    if (strnlen(src, dest_size) >= dest_size) {
        return -1;
    }

    written = snprintf(dest, dest_size, "%s", src);
    if (written < 0 || (size_t)written >= dest_size) {
        return -1;
    }
    return 0;
}

static int max_aggregate(const Tuple *tuples, size_t count, Aggregate *result)
{
    Aggregate *aggs;
    size_t agg_count = 0;
    size_t i;
    size_t max_index = 0;
    int status = -1;

    if (tuples == NULL || result == NULL || count == 0 || count > MAX_ENTRIES) {
        return -1;
    }

    aggs = calloc(count, sizeof(Aggregate));
    if (aggs == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        int idx;

        if (strnlen(tuples[i].name, MAX_NAME_LEN) >= MAX_NAME_LEN) {
            free(aggs);
            return -1;
        }

        idx = find_aggregate(aggs, agg_count, tuples[i].name);
        if (idx >= 0 && (size_t)idx < agg_count) {
            aggs[idx].total += tuples[i].score;
        } else {
            if (agg_count >= count) {
                free(aggs);
                return -1;
            }
            if (copy_name(aggs[agg_count].name, sizeof(aggs[agg_count].name),
                          tuples[i].name) != 0) {
                free(aggs);
                return -1;
            }
            aggs[agg_count].total = tuples[i].score;
            agg_count++;
        }
    }

    if (agg_count == 0) {
        free(aggs);
        return -1;
    }

    for (i = 1; i < agg_count; i++) {
        if (aggs[i].total > aggs[max_index].total) {
            max_index = i;
        }
    }

    if (copy_name(result->name, sizeof(result->name),
                  aggs[max_index].name) == 0) {
        result->total = aggs[max_index].total;
        status = 0;
    }

    free(aggs);
    return status;
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

    memset(&result, 0, sizeof(result));

    if (max_aggregate(tuples, count, &result) != 0) {
        fprintf(stderr, "Failed to compute maximum aggregate\n");
        return EXIT_FAILURE;
    }

    if (printf("(%s, %d)\n", result.name, result.total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}