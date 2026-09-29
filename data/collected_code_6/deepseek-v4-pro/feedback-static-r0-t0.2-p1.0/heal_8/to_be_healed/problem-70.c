#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int length;
} Tuple;

bool all_tuples_equal_length(const Tuple *tuples, int tuple_count) {
    if (tuples == NULL || tuple_count <= 0) {
        return false;
    }
    
    int first_length = tuples[0].length;
    
    for (int i = 1; i < tuple_count; i++) {
        if (tuples[i].length != first_length) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    Tuple tuples[] = {
        {3},
        {3},
        {3}
    };
    
    if (all_tuples_equal_length(tuples, 3)) {
        printf("All tuples have equal length\n");
    } else {
        printf("Tuples have different lengths\n");
    }
    
    /* Possible weaknesses found:
     *  Variable 'tuples2' can be declared as const array [constVariable]
     */
    Tuple tuples2[] = {
        {3},
        {2},
        {3}
    };
    
    if (all_tuples_equal_length(tuples2, 3)) {
        printf("All tuples have equal length\n");
    } else {
        printf("Tuples have different lengths\n");
    }
    
    return 0;
}