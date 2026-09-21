#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define TUPLE_NAME_MAX 32U

typedef struct {
    char name[TUPLE_NAME_MAX];
    int *records;
    size_t record_count;
} Tuple;

static bool set_tuple_name(Tuple *tuple, const char *name)
{
    int written;
    size_t name_len;

    if (tuple == NULL || name == NULL) {
        return false;
    }

    name_len = strnlen(name, sizeof(tuple->name));
    if (name_len >= sizeof(tuple->name)) {
        tuple->name[0] = '\0';
        return false;
    }

    written = snprintf(tuple->name, sizeof(tuple->name), "%s", name);
    if (written < 0 || (size_t)written >= sizeof(tuple->name)) {
        tuple->name[sizeof(tuple->name) - 1U] = '\0';
        return false;
    }

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

    if (find_max_record(tuples, sizeof(tuples) / sizeof(tuples[0]), &max_value)) {
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