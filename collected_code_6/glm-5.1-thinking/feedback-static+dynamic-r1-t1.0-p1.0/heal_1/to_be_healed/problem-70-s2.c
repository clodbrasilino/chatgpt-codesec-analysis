#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

bool check_equal_lengths(const Tuple *tuples, size_t num_tuples) {
    if (num_tuples == 0) {
        return true;
    }
    
    if (tuples == NULL) {
        return false;
    }

    size_t expected_length = tuples[0].length;

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i].data == NULL && tuples[i].length > 0) {
            return false;
        }
        if (tuples[i].length != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int d1[] = {1, 2};
    int d2[] = {3, 4};
    int d3[] = {5, 6};

    /* Possible weaknesses found:
     *  Variable 't1' can be declared as const array [constVariable]
     */
    Tuple t1[] = {
        {d1, 2},
        {d2, 2},
        {d3, 2}
    };

    bool res1 = check_equal_lengths(t1, 3);
    printf("%s\n", res1 ? "true" : "false");

    int d4[] = {7, 8, 9};
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as const array [constVariable]
     */
    Tuple t2[] = {
        {d1, 2},
        {d4, 3}
    };

    bool res2 = check_equal_lengths(t2, 2);
    printf("%s\n", res2 ? "true" : "false");

    /* Possible weaknesses found:
     *  Assignment 'res3=check_equal_lengths(NULL,0)', assigned value is 1
     *  Calling function 'check_equal_lengths' returns 1
     */
    bool res3 = check_equal_lengths(NULL, 0);
    /* Possible weaknesses found:
     *  Condition 'res3' is always true
     *  Condition 'res3' is always true [knownConditionTrueFalse]
     */
    printf("%s\n", res3 ? "true" : "false");

    /* Possible weaknesses found:
     *  Calling function 'check_equal_lengths' returns 0
     *  Assignment 'res4=check_equal_lengths(NULL,1)', assigned value is 0
     */
    bool res4 = check_equal_lengths(NULL, 1);
    /* Possible weaknesses found:
     *  Condition 'res4' is always false [knownConditionTrueFalse]
     *  Condition 'res4' is always false
     */
    printf("%s\n", res4 ? "true" : "false");

    /* Possible weaknesses found:
     *  Variable 't3' can be declared as const array [constVariable]
     */
    Tuple t3[] = {
        {NULL, 0},
        {d1, 0}
    };

    bool res5 = check_equal_lengths(t3, 2);
    printf("%s\n", res5 ? "true" : "false");

    return 0;
}