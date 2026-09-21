#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

static int safe_add(int a, int b, int *out)
{
    if (out == NULL) {
        return -1;
    }
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return -1;
    }
    *out = a + b;
    return 0;
}

static int copy_aggregate(Aggregate *dest, size_t dest_size, const Aggregate *src)
{
    if (dest == NULL || src == NULL || dest_size < sizeof(Aggregate)) {
        return -1;
    }

    if (copy_name(dest->name, sizeof(dest->name), src->name) != 0) {
        return -1;
    }
    dest->total = src->total;
    dest->name[MAX_NAME_LEN - 1] = '\0';
    return 0;
}

static int max_aggregate(const Tuple *tuples, size_t n, Aggregate *result)
{
    Aggregate aggs[MAX_ENTRIES];
    size_t count = 0;
    size_t i;
    size_t max_idx = 0;

    if (tuples == NULL || result == NULL || n == 0 || n > MAX_ENTRIES) {
        return -1;
    }

    memset(aggs, 0, sizeof(aggs));

    for (i = 0; i < n; i++) {
        int idx;

        if (strnlen(tuples[i].name, MAX_NAME_LEN) >= MAX_NAME_LEN) {
            return -1;
        }

        idx = find_aggregate(aggs, count, tuples[i].name);
        if (idx >= 0) {
            if (safe_add(aggs[idx].total, tuples[i].score, &aggs[idx].total) != 0) {
                return -1;
            }
        } else {
            if (count >= MAX_ENTRIES) {
                return -1;
            }
            if (copy_name(aggs[count].name, sizeof(aggs[count].name), tuples[i].name) != 0) {
                return -1;
            }
            aggs[count].total = tuples[i].score;
            count++;
        }
    }

    if (count == 0) {
        return -1;
    }

    for (i = 1; i < count; i++) {
        if (aggs[i].total > aggs[max_idx].total) {
            max_idx = i;
        }
    }

    if (copy_aggregate(result, sizeof(*result), &aggs[max_idx]) != 0) {
        return -1;
    }

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
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    Aggregate result;

    memset(&result, 0, sizeof(result));

    if (max_aggregate(tuples, n, &result) != 0) {
        fprintf(stderr, "Error computing maximum aggregate\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum aggregate: %s with %d\n", result.name, result.total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}