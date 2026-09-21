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

static int safe_copy_name(char *dest, size_t dest_size, const char *src)
{
    size_t len;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    len = strnlen(src, dest_size);
    if (len >= dest_size) {
        return -1;
    }

    memset(dest, 0, dest_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len);
    dest[len] = '\0';

    return 0;
}

static int max_aggregate(const StudentTuple *tuples, size_t count,
                         char *out_name, size_t out_name_size,
                         long *out_total)
{
    Aggregate aggregates[MAX_ENTRIES];
    size_t agg_count = 0;
    size_t i;
    size_t j;
    size_t max_index = 0;
    size_t name_len;

    if (tuples == NULL || out_name == NULL || out_total == NULL) {
        return -1;
    }
    if (count == 0 || out_name_size == 0) {
        return -1;
    }

    memset(aggregates, 0, sizeof(aggregates));

    for (i = 0; i < count; i++) {
        int found = 0;

        name_len = strnlen(tuples[i].name, MAX_NAME_LEN);
        if (name_len >= MAX_NAME_LEN) {
            return -1;
        }

        for (j = 0; j < agg_count; j++) {
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
            if (safe_copy_name(aggregates[agg_count].name, MAX_NAME_LEN,
                               tuples[i].name) != 0) {
                return -1;
            }
            aggregates[agg_count].total = (long)tuples[i].score;
            agg_count++;
        }
    }

    if (agg_count == 0) {
        return -1;
    }

    for (j = 1; j < agg_count; j++) {
        if (aggregates[j].total > aggregates[max_index].total) {
            max_index = j;
        }
    }

    name_len = strnlen(aggregates[max_index].name, MAX_NAME_LEN);
    if (name_len >= out_name_size) {
        return -1;
    }

    if (safe_copy_name(out_name, out_name_size, aggregates[max_index].name) != 0) {
        return -1;
    }

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
    char result_name[MAX_NAME_LEN] = {0};
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