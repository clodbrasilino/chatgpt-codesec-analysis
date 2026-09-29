#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains_only_k_elements(const int *tuple, size_t size, size_t k)
{
    if (tuple == NULL) {
        return false;
    }
    return size == k;
}

int main(void)
{
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {7, 8, 9};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    const int *null_tuple = NULL;

    if (contains_only_k_elements(tuple1, size1, 4)) {
        printf("Tuple 1 contains exactly 4 elements\n");
    } else {
        printf("Tuple 1 does not contain exactly 4 elements\n");
    }

    if (contains_only_k_elements(tuple2, size2, 4)) {
        printf("Tuple 2 contains exactly 4 elements\n");
    } else {
        printf("Tuple 2 does not contain exactly 4 elements\n");
    }

    /* Possible weaknesses found:
     *  Condition '!contains_only_k_elements(null_tuple,0,0)' is always true
     *  Calling function 'contains_only_k_elements' returns 0
     *  Condition '!contains_only_k_elements(null_tuple,0,0)' is always true [knownConditionTrueFalse]
     */
    if (!contains_only_k_elements(null_tuple, 0, 0)) {
        printf("NULL tuple handled safely\n");
    }

    return EXIT_SUCCESS;
}