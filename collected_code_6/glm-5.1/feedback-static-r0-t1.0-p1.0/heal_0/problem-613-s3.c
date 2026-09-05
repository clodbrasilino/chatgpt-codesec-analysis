#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int *records;
    size_t records_len;
} Tuple;

int find_max_in_records(Tuple *tuples, size_t tuples_len, size_t *error_flag) {
    int max_val = INT_MIN;
    *error_flag = 0;

    if (tuples == NULL || tuples_len == 0) {
        *error_flag = 1;
        return INT_MIN;
    }

    for (size_t i = 0; i < tuples_len; i++) {
        if (tuples[i].records == NULL) {
            if (tuples[i].records_len > 0) {
                *error_flag = 1;
                return INT_MIN;
            }
            continue;
        }

        for (size_t j = 0; j < tuples[i].records_len; j++) {
            if (tuples[i].records[j] > max_val) {
                max_val = tuples[i].records[j];
            }
        }
    }

    return max_val;
}

int main(void) {
    int rec1[] = {3, 1, 4};
    int rec2[] = {1, 5, 9, 2};
    int rec3[] = {6, 5, 3};

    Tuple tuples[] = {
        {1, rec1, 3},
        {2, rec2, 4},
        {3, rec3, 3}
    };

    size_t tuples_len = sizeof(tuples) / sizeof(tuples[0]);
    size_t error_flag = 0;

    int max_val = find_max_in_records(tuples, tuples_len, &error_flag);

    if (error_flag) {
        return EXIT_FAILURE;
    }

    printf("%d\n", max_val);

    return EXIT_SUCCESS;
}