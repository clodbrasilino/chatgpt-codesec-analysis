#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

bool check_equal_lengths(const Tuple *tuples, size_t num_tuples) {
    if (num_tuples == 0) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    size_t expected_length = tuples[0].length;

    if (tuples[0].data == NULL && tuples[0].length > 0) {
        return false;
    }

    for (size_t i = 1; i < num_tuples; i++) {
        if (tuples[i].data == NULL && tuples[i].length > 0) {
            return false;
        }
        if (tuples[i].length != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *bool_str[] = {"false", "true"};

    int d1[] = {1, 2};
    int d2[] = {3, 4};
    int d3[] = {5, 6};

    const Tuple t1[] = {
        {d1, 2},
        {d2, 2},
        {d3, 2}
    };

    printf("%s\n", bool_str[check_equal_lengths(t1, 3)]);

    int d4[] = {7, 8, 9};
    const Tuple t2[] = {
        {d1, 2},
        {d4, 3}
    };

    printf("%s\n", bool_str[check_equal_lengths(t2, 2)]);
    printf("%s\n", bool_str[check_equal_lengths(NULL, 0)]);
    printf("%s\n", bool_str[check_equal_lengths(NULL, 1)]);

    const Tuple t3[] = {
        {NULL, 0},
        {d1, 0}
    };

    printf("%s\n", bool_str[check_equal_lengths(t3, 2)]);

    return 0;
}