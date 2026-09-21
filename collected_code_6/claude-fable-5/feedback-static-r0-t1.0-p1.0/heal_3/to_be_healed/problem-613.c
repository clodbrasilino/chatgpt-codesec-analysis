#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define NAME_MAX_LEN 32U

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_MAX_LEN];
    int *records;
    size_t record_count;
} Tuple;

static bool set_tuple_name(Tuple *tuple, const char *name)
{
    size_t len;

    if (tuple == NULL || name == NULL) {
        return false;
    }

    len = strnlen(name, sizeof(tuple->name));
    if (len >= sizeof(tuple->name)) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->name, name, len);
    tuple->name[len] = '\0';
    return true;
}

bool find_max_record(const Tuple *tuples, size_t tuple_count, int *max_out)
{
    bool found = false;
    int max_val = INT_MIN;
    size_t i;
    size_t j;

    if (tuples == NULL || max_out == NULL || tuple_count == 0U) {
        return false;
    }

    for (i = 0U; i < tuple_count; i++) {
        if (tuples[i].records == NULL) {
            continue;
        }
        for (j = 0U; j < tuples[i].record_count; j++) {
            if (!found || tuples[i].records[j] > max_val) {
                max_val = tuples[i].records[j];
                found = true;
            }
        }
    }

    if (!found) {
        return false;
    }

    *max_out = max_val;
    return true;
}

int main(void)
{
    int records1[] = {3, 7, 2};
    int records2[] = {15, 4};
    int records3[] = {9, 11, 6, 8};
    Tuple tuples[3];
    int max_value = 0;

    memset(tuples, 0, sizeof(tuples));

    tuples[0].records = records1;
    tuples[0].record_count = sizeof(records1) / sizeof(records1[0]);
    if (!set_tuple_name(&tuples[0], "alpha")) {
        return EXIT_FAILURE;
    }

    tuples[1].records = records2;
    tuples[1].record_count = sizeof(records2) / sizeof(records2[0]);
    if (!set_tuple_name(&tuples[1], "beta")) {
        return EXIT_FAILURE;
    }

    tuples[2].records = records3;
    tuples[2].record_count = sizeof(records3) / sizeof(records3[0]);
    if (!set_tuple_name(&tuples[2], "gamma")) {
        return EXIT_FAILURE;
    }

    if (find_max_record(tuples, 3U, &max_value)) {
        if (printf("Maximum record value: %d\n", max_value) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "No records found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}