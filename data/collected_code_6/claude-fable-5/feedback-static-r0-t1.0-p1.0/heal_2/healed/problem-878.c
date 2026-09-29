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
    const int *null_tuple = NULL;
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t null_size = 0;
    size_t k = 6;
    size_t null_k = 0;

    bool result1 = check_tuple_has_k_elements(tuple1, size1, k);
    bool result2 = check_tuple_has_k_elements(tuple2, size2, k);
    bool result3 = check_tuple_has_k_elements(null_tuple, null_size, null_k);

    print_result("tuple1 contains exactly 6 elements", result1);
    print_result("tuple2 contains exactly 6 elements", result2);
    print_result("NULL tuple check", result3);

    return EXIT_SUCCESS;
}