#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

bool have_equal_lengths(const Tuple *tuples, size_t count);

bool have_equal_lengths(const Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return false;
    }

    if (count <= 1) {
        return true;
    }

    size_t first_length = tuples[0].length;

    for (size_t i = 1; i < count; i++) {
        if (tuples[i].length != first_length) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int tuple1_data[] = {1, 2, 3};
    int tuple2_data[] = {4, 5, 6};
    int tuple3_data[] = {7, 8, 9};

    Tuple equal_tuples[] = {
        {tuple1_data, sizeof(tuple1_data) / sizeof(tuple1_data[0])},
        {tuple2_data, sizeof(tuple2_data) / sizeof(tuple2_data[0])},
        {tuple3_data, sizeof(tuple3_data) / sizeof(tuple3_data[0])}
    };

    size_t equal_count = sizeof(equal_tuples) / sizeof(equal_tuples[0]);

    if (have_equal_lengths(equal_tuples, equal_count)) {
        printf("Equal lengths\n");
    } else {
        printf("Unequal lengths\n");
    }

    int tuple4_data[] = {1, 2};

    Tuple unequal_tuples[] = {
        {tuple1_data, sizeof(tuple1_data) / sizeof(tuple1_data[0])},
        {tuple4_data, sizeof(tuple4_data) / sizeof(tuple4_data[0])},
        {tuple3_data, sizeof(tuple3_data) / sizeof(tuple3_data[0])}
    };

    size_t unequal_count = sizeof(unequal_tuples) / sizeof(unequal_tuples[0]);

    if (have_equal_lengths(unequal_tuples, unequal_count)) {
        printf("Equal lengths\n");
    } else {
        printf("Unequal lengths\n");
    }

    return 0;
}