#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t length;
} Tuple;

bool all_tuples_same_length(const Tuple *tuples, size_t count) {
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
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t len3 = sizeof(tuple3) / sizeof(tuple3[0]);

    Tuple tuples[] = {
        {len1},
        {len2},
        {len3}
    };

    bool same_len = all_tuples_same_length(tuples, sizeof(tuples) / sizeof(tuples[0]));
    puts(same_len ? "true" : "false");

    int tuple4[] = {10, 11};
    size_t len4 = sizeof(tuple4) / sizeof(tuple4[0]);

    Tuple mixed[] = {
        {len1},
        {len4}
    };

    bool mixed_same_len = all_tuples_same_length(mixed, sizeof(mixed) / sizeof(mixed[0]));
    puts(mixed_same_len ? "true" : "false");

    Tuple empty[] = {
        {0}
    };

    bool empty_same_len = all_tuples_same_length(empty, sizeof(empty) / sizeof(empty[0]));
    puts(empty_same_len ? "true" : "false");

    return 0;
}