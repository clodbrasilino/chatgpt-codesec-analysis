#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::elements' is never used. [unusedStructMember]
     */
    int *elements;
    size_t length;
} Tuple;

bool all_tuples_equal_length(const Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL || tuple_count == 0) {
        return true;
    }
    
    size_t first_length = tuples[0].length;
    
    for (size_t i = 1; i < tuple_count; i++) {
        if (tuples[i].length != first_length) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int tuple1_elements[] = {1, 2, 3};
    int tuple2_elements[] = {4, 5, 6};
    int tuple3_elements[] = {7, 8, 9};
    int tuple4_elements[] = {10, 11};
    
    Tuple tuple1 = {tuple1_elements, 3};
    Tuple tuple2 = {tuple2_elements, 3};
    Tuple tuple3 = {tuple3_elements, 3};
    
    const Tuple tuples[] = {tuple1, tuple2, tuple3};
    
    bool result1 = all_tuples_equal_length(tuples, 3);
    
    if (result1) {
        printf("All tuples equal length (test 1): true\n");
    } else {
        printf("All tuples equal length (test 1): false\n");
    }
    
    const Tuple tuples2[] = {
        {tuple1_elements, 3},
        {tuple2_elements, 3},
        {tuple4_elements, 2}
    };
    
    bool result2 = all_tuples_equal_length(tuples2, 3);
    
    if (result2) {
        printf("All tuples equal length (test 2): true\n");
    } else {
        printf("All tuples equal length (test 2): false\n");
    }
    
    /* Possible weaknesses found:
     *  Assignment 'result3=all_tuples_equal_length(NULL,0)', assigned value is 1
     *  Calling function 'all_tuples_equal_length' returns 1
     */
    bool result3 = all_tuples_equal_length(NULL, 0);
    printf("All tuples equal length (empty): %s\n", 
           /* Possible weaknesses found:
            *  Condition 'result3' is always true
            *  Condition 'result3' is always true [knownConditionTrueFalse]
            */
           result3 ? "true" : "false");
    
    bool result4 = all_tuples_equal_length(tuples, 0);
    printf("All tuples equal length (zero count): %s\n", 
           result4 ? "true" : "false");
    
    return 0;
}