#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_tuples_equal_length(const int *tuples, const size_t *tuple_lengths, size_t tuple_count) {
    if (tuple_count == 0) {
        return true;
    }
    if (tuples == NULL || tuple_lengths == NULL) {
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
    
    const int *tuples[] = {tuple1, tuple2, tuple3};
    const size_t tuple_lengths[] = {3, 3, 3};
    
    bool result = all_tuples_equal_length((const int *)tuples, tuple_lengths, 3);
    printf("All tuples equal length: %s\n", result ? "true" : "false");
    
    const size_t different_lengths[] = {3, 2, 3};
    result = all_tuples_equal_length((const int *)tuples, different_lengths, 3);
    printf("All tuples equal length: %s\n", result ? "true" : "false");
    
    return 0;
}