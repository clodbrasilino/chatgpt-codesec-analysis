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
    /* Possible weaknesses found:
     *  Variable 'tuple_lengths' can be declared as const array [constVariable]
     */
    size_t tuple_lengths[] = {3, 3, 3};
    
    bool result = all_tuples_equal_length((const int *)tuples, tuple_lengths, 3);
    printf("All tuples equal length: %s\n", result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Variable 'tuple_lengths2' can be declared as const array [constVariable]
     */
    size_t tuple_lengths2[] = {3, 2, 3};
    result = all_tuples_equal_length((const int *)tuples, tuple_lengths2, 3);
    printf("All tuples equal length: %s\n", result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'result=all_tuples_equal_length(NULL,NULL,0)', assigned value is 1
     *  Calling function 'all_tuples_equal_length' returns 1
     */
    result = all_tuples_equal_length(NULL, NULL, 0);
    /* Possible weaknesses found:
     *  Condition 'result' is always true [knownConditionTrueFalse]
     *  Condition 'result' is always true
     */
    printf("Empty tuple set: %s\n", result ? "true" : "false");
    
    return 0;
}