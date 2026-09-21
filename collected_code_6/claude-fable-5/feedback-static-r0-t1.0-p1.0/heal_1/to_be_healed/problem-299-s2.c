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
    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         *  Uninitialized variable: aggs.total
         *  Uninitialized variable: aggs.total [uninitvar]
         */
        if (strcmp(aggs[i].name, name) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static int max_aggregate(const Tuple *tuples, size_t n, Aggregate *result)
{
    Aggregate aggs[MAX_ENTRIES];
    size_t count = 0;
    size_t i;
    size_t max_idx = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'idx' can be reduced. [variableScope]
     */
    int idx;

    if (tuples == NULL || result == NULL || n == 0 || n > MAX_ENTRIES) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Calling function 'find_aggregate', 1st argument 'aggs' value is <Uninit>
         */
        idx = find_aggregate(aggs, count, tuples[i].name);
        if (idx >= 0) {
            aggs[idx].total += tuples[i].score;
        } else {
            if (count >= MAX_ENTRIES) {
                return -1;
            }
            if (snprintf(aggs[count].name, MAX_NAME_LEN, "%s", tuples[i].name) < 0) {
                return -1;
            }
            aggs[count].total = tuples[i].score;
            count++;
        }
    }

    for (i = 1; i < count; i++) {
        if (aggs[i].total > aggs[max_idx].total) {
            max_idx = i;
        }
    }

    *result = aggs[max_idx];
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

    if (max_aggregate(tuples, n, &result) != 0) {
        fprintf(stderr, "Error computing maximum aggregate\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum aggregate: %s with %d\n", result.name, result.total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}