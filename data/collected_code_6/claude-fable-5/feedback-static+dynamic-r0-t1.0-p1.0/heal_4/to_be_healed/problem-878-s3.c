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

static void report(const char *name, bool result, size_t k)
{
    if (result) {
        printf("%s contains exactly %zu elements\n", name, k);
    } else {
        printf("%s does not contain exactly %zu elements\n", name, k);
    }
}

int main(void)
{
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {7, 8, 9};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    const int *null_tuple = NULL;

    report("Tuple 1", contains_only_k_elements(tuple1, size1, 4), 4);
    report("Tuple 2", contains_only_k_elements(tuple2, size2, 4), 4);

    /* Possible weaknesses found:
     *  Condition 'contains_only_k_elements(null_tuple,0,0)' is always false [knownConditionTrueFalse]
     *  Condition 'contains_only_k_elements(null_tuple,0,0)' is always false
     *  Calling function 'contains_only_k_elements' returns 0
     */
    if (contains_only_k_elements(null_tuple, 0, 0)) {
        printf("NULL tuple handled safely\n");
    } else {
        printf("NULL tuple rejected\n");
    }

    return EXIT_SUCCESS;
}