#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    void *data;
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
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int tuple3[] = {7, 8, 9};

    Tuple tuples[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };

    bool equal = all_tuples_equal_length(tuples, sizeof(tuples) / sizeof(tuples[0]));
    printf("%s\n", equal ? "true" : "false");

    int tuple4[] = {10, 11};

    Tuple mixed[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple4, sizeof(tuple4) / sizeof(tuple4[0])}
    };

    bool mixed_equal = all_tuples_equal_length(mixed, sizeof(mixed) / sizeof(mixed[0]));
    printf("%s\n", mixed_equal ? "true" : "false");

    Tuple empty[] = {
        {NULL, 0}
    };

    bool empty_equal = all_tuples_equal_length(empty, sizeof(empty) / sizeof(empty[0]));
    printf("%s\n", empty_equal ? "true" : "false");

    return 0;
}