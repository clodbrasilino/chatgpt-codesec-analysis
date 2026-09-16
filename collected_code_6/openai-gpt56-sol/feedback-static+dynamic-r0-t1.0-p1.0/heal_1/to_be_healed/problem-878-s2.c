#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool tuple_contains_only_k_elements(size_t tuple_size, size_t k)
{
    return tuple_size == k;
}

int main(void)
{
    int tuple[] = {1, 2, 3};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const size_t k = 3U;

    if (printf("%s\n",
               /* Possible weaknesses found:
                *  Calling function 'tuple_contains_only_k_elements' returns 1
                *  Condition 'tuple_contains_only_k_elements(tuple_size,k)' is always true [knownConditionTrueFalse]
                *  Condition 'tuple_contains_only_k_elements(tuple_size,k)' is always true
                */
               tuple_contains_only_k_elements(tuple_size, k) ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}