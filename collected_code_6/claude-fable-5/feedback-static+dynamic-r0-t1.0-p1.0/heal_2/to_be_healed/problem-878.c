#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuple_has_k_elements(const int *tuple, size_t size, size_t k)
{
    if (tuple == NULL)
    {
        return k == 0 && size == 0;
    }
    return size == k;
}

int main(void)
{
    int tuple1[] = {3, 5, 6, 5, 3, 6};
    int tuple2[] = {1, 2, 3};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    printf("tuple1 contains exactly 6 elements: %s\n",
           check_tuple_has_k_elements(tuple1, size1, 6) ? "true" : "false");

    printf("tuple2 contains exactly 6 elements: %s\n",
           check_tuple_has_k_elements(tuple2, size2, 6) ? "true" : "false");

    printf("NULL tuple check: %s\n",
           /* Possible weaknesses found:
            *  Condition 'check_tuple_has_k_elements(NULL,0,0)' is always true
            *  Calling function 'check_tuple_has_k_elements' returns 1
            *  Condition 'check_tuple_has_k_elements(NULL,0,0)' is always true [knownConditionTrueFalse]
            */
           check_tuple_has_k_elements(NULL, 0, 0) ? "true" : "false");

    return EXIT_SUCCESS;
}