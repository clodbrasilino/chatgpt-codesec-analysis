#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuple_has_k_elements(const int *tuple, size_t size, size_t k)
{
    if (tuple == NULL)
    {
        return false;
    }
    return size == k;
}

static void print_result(const char *label, bool result)
{
    printf("%s: %s\n", label, result ? "true" : "false");
}

int main(void)
{
    int tuple1[] = {3, 5, 6, 5, 3, 6};
    int tuple2[] = {1, 2, 3};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    const int *null_tuple = NULL;
    size_t null_size = 0;

    print_result("Tuple 1 contains exactly 6 elements",
                 check_tuple_has_k_elements(tuple1, size1, 6));

    print_result("Tuple 2 contains exactly 6 elements",
                 check_tuple_has_k_elements(tuple2, size2, 6));

    print_result("NULL tuple check",
                 check_tuple_has_k_elements(null_tuple, null_size, 0));

    return EXIT_SUCCESS;
}