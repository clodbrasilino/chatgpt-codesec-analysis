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
} StudentTuple;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    long total;
} Aggregate;

static int max_aggregate(const StudentTuple *tuples, size_t count,
                         char *out_name, size_t out_name_size,
                         long *out_total)
{
    Aggregate aggregates[MAX_ENTRIES];
    size_t agg_count = 0;
    size_t i;
    size_t j;
    size_t max_index = 0;

    if (tuples == NULL || out_name == NULL || out_total == NULL) {
        return -1;
    }
    if (count == 0 || out_name_size == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        int found = 0;
        for (j = 0; j < agg_count; j++) {
            /* Possible weaknesses found:
             *  Uninitialized variable: aggregates.total [uninitvar]
             */
            if (strncmp(aggregates[j].name, tuples[i].name, MAX_NAME_LEN) == 0) {
                aggregates[j].total += (long)tuples[i].score;
                found = 1;
                break;
            }
        }
        if (found == 0) {
            if (agg_count >= MAX_ENTRIES) {
                return -1;
            }
            memset(aggregates[agg_count].name, 0, MAX_NAME_LEN);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(aggregates[agg_count].name, tuples[i].name, MAX_NAME_LEN - 1);
            aggregates[agg_count].total = (long)tuples[i].score;
            agg_count++;
        }
    }

    for (j = 1; j < agg_count; j++) {
        if (aggregates[j].total > aggregates[max_index].total) {
            max_index = j;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(aggregates[max_index].name) >= out_name_size) {
        return -1;
    }

    memset(out_name, 0, out_name_size);
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(out_name, aggregates[max_index].name, out_name_size - 1);
    *out_total = aggregates[max_index].total;

    return 0;
}

int main(void)
{
    StudentTuple data[] = {
        {"Juan Whelan", 90},
        {"Sabah Colley", 88},
        {"Peter Nichols", 7},
        {"Juan Whelan", 122},
        {"Sabah Colley", 84}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result_name[MAX_NAME_LEN];
    long result_total = 0;
    int status;

    status = max_aggregate(data, count, result_name, sizeof(result_name), &result_total);
    if (status != 0) {
        fprintf(stderr, "Error: failed to compute maximum aggregate\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum aggregate: (%s, %ld)\n", result_name, result_total) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}