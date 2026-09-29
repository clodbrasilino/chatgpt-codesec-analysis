#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_tuples_equal_length(const int *const *tuples, size_t tuple_count, const size_t *tuple_lengths) {
    if (tuples == NULL || tuple_lengths == NULL || tuple_count == 0) {
        return false;
    }

    size_t first_length = tuple_lengths[0];
    for (size_t i = 1; i < tuple_count; i++) {
        if (tuple_lengths[i] != first_length) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int tuple3[] = {7, 8, 9};
    int tuple4[] = {10, 11};

    const int *tuples1[] = {tuple1, tuple2, tuple3};
    const size_t lengths1[] = {3, 3, 3};

    const int *tuples2[] = {tuple1, tuple2, tuple4};
    const size_t lengths2[] = {3, 3, 2};

    const int *tuples3[] = {tuple1, tuple2};
    const size_t lengths3[] = {3, 3};

    printf("Test 1: %s\n", all_tuples_equal_length(tuples1, 3, lengths1) ? "true" : "false");
    printf("Test 2: %s\n", all_tuples_equal_length(tuples2, 3, lengths2) ? "true" : "false");
    printf("Test 3: %s\n", all_tuples_equal_length(tuples3, 2, lengths3) ? "true" : "false");

    bool test4_result = all_tuples_equal_length(NULL, 3, lengths1);
    if (!test4_result) {
        printf("Test 4: false\n");
    } else {
        printf("Test 4: true\n");
    }

    bool test5_result = all_tuples_equal_length(tuples1, 0, lengths1);
    if (!test5_result) {
        printf("Test 5: false\n");
    } else {
        printf("Test 5: true\n");
    }

    return 0;
}