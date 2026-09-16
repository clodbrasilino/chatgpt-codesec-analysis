#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains_only_k_elements(const int *tuple, size_t size, size_t k, bool *result)
{
    if (result == NULL) {
        return false;
    }
    if (tuple == NULL) {
        *result = false;
        return false;
    }
    *result = (size == k);
    return true;
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
    bool result = false;

    if (contains_only_k_elements(tuple1, size1, 4, &result)) {
        report("Tuple 1", result, 4);
    } else {
        printf("Tuple 1 is invalid\n");
    }

    if (contains_only_k_elements(tuple2, size2, 4, &result)) {
        report("Tuple 2", result, 4);
    } else {
        printf("Tuple 2 is invalid\n");
    }

    if (contains_only_k_elements(null_tuple, 0, 0, &result)) {
        report("NULL tuple", result, 0);
    } else {
        printf("NULL tuple rejected\n");
    }

    return EXIT_SUCCESS;
}