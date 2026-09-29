#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

bool are_tuple_lengths_equal(const Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL) {
        return false;
    }
    
    if (tuple_count == 0) {
        return true;
    }
    
    if (tuples[0].items == NULL && tuples[0].length > 0) {
        return false;
    }
    
    size_t reference_length = tuples[0].length;
    
    for (size_t i = 1; i < tuple_count; i++) {
        if (tuples[i].items == NULL && tuples[i].length > 0) {
            return false;
        }
        if (tuples[i].length != reference_length) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {7, 8, 9};
    
    const Tuple equal_tuples[] = {
        {arr1, 3},
        {arr2, 3},
        {arr3, 3}
    };
    
    int arr4[] = {10, 11};
    const Tuple unequal_tuples[] = {
        {arr1, 3},
        {arr4, 2}
    };
    
    const Tuple empty_tuples[] = {
        {NULL, 0},
        {NULL, 0}
    };
    
    if (are_tuple_lengths_equal(equal_tuples, 3)) {
        printf("equal_tuples: All lengths are equal.\n");
    } else {
        printf("equal_tuples: Lengths are not equal.\n");
    }
    
    if (are_tuple_lengths_equal(unequal_tuples, 2)) {
        printf("unequal_tuples: All lengths are equal.\n");
    } else {
        printf("unequal_tuples: Lengths are not equal.\n");
    }
    
    if (are_tuple_lengths_equal(empty_tuples, 2)) {
        printf("empty_tuples: All lengths are equal.\n");
    } else {
        printf("empty_tuples: Lengths are not equal.\n");
    }
    
    return 0;
}