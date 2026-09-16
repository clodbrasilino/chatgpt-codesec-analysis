#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    const int *data;
    size_t length;
} Tuple;

bool all_tuples_equal_length(const Tuple *tuples, size_t count) {
    if (count == 0) {
        return true;
    }
    if (tuples == NULL) {
        return false;
    }
    size_t expected = tuples[0].length;
    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].length != expected) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const int tuple_data_1[] = {1, 2, 3};
    const int tuple_data_2[] = {4, 5, 6};
    const int tuple_data_3[] = {7, 8, 9};
    const int tuple_data_4[] = {10, 11};

    Tuple equal_tuples[] = {
        {tuple_data_1, 3},
        {tuple_data_2, 3},
        {tuple_data_3, 3}
    };

    Tuple unequal_tuples[] = {
        {tuple_data_1, 3},
        {tuple_data_4, 2},
        {tuple_data_3, 3}
    };

    Tuple single_tuple[] = {
        {tuple_data_1, 3}
    };

    printf("%d\n", all_tuples_equal_length(equal_tuples, 3));
    printf("%d\n", all_tuples_equal_length(unequal_tuples, 3));
    printf("%d\n", all_tuples_equal_length(single_tuple, 1));
    printf("%d\n", all_tuples_equal_length(NULL, 0));

    return 0;
}