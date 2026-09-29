#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

bool all_tuples_equal_length(const Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return false;
    }

    if (count == 0 || count == 1) {
        return true;
    }

    size_t first_length = tuples[0].length;

    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].length != first_length) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int data_a[] = {1, 2, 3};
    int data_b[] = {4, 5, 6};
    int data_c[] = {7, 8, 9};
    int data_d[] = {10, 11};

    Tuple group1[] = {
        {data_a, sizeof(data_a) / sizeof(data_a[0])},
        {data_b, sizeof(data_b) / sizeof(data_b[0])},
        {data_c, sizeof(data_c) / sizeof(data_c[0])}
    };

    Tuple group2[] = {
        {data_a, sizeof(data_a) / sizeof(data_a[0])},
        {data_d, sizeof(data_d) / sizeof(data_d[0])},
        {data_c, sizeof(data_c) / sizeof(data_c[0])}
    };

    size_t group1_count = sizeof(group1) / sizeof(group1[0]);
    size_t group2_count = sizeof(group2) / sizeof(group2[0]);

    bool result1 = all_tuples_equal_length(group1, group1_count);
    bool result2 = all_tuples_equal_length(group2, group2_count);

    if (result1) {
        printf("Group 1: All tuples have equal length.\n");
    } else {
        printf("Group 1: Tuples have different lengths.\n");
    }

    if (result2) {
        printf("Group 2: All tuples have equal length.\n");
    } else {
        printf("Group 2: Tuples have different lengths.\n");
    }

    return 0;
}