#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

bool are_tuple_lengths_equal(const Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return false;
    }
    if (count == 0) {
        return true;
    }
    size_t expected_length = tuples[0].length;
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].length != expected_length) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int c[] = {7, 8};

    Tuple list1[] = {{a, 3}, {b, 3}};
    Tuple list2[] = {{a, 3}, {c, 2}};

    printf("%d\n", are_tuple_lengths_equal(list1, 2));
    printf("%d\n", are_tuple_lengths_equal(list2, 2));
    printf("%d\n", are_tuple_lengths_equal(NULL, 2));
    printf("%d\n", are_tuple_lengths_equal(list1, 0));

    return 0;
}