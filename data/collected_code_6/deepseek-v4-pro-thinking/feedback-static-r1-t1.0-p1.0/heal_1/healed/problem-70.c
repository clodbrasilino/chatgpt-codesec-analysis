#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
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
    const Tuple equal_tuples[] = {
        {3},
        {3},
        {3}
    };

    const Tuple unequal_tuples[] = {
        {3},
        {2},
        {3}
    };

    const Tuple single_tuple[] = {
        {3}
    };

    printf("%d\n", all_tuples_equal_length(equal_tuples, 3));
    printf("%d\n", all_tuples_equal_length(unequal_tuples, 3));
    printf("%d\n", all_tuples_equal_length(single_tuple, 1));
    printf("%d\n", all_tuples_equal_length(NULL, 0));

    return 0;
}