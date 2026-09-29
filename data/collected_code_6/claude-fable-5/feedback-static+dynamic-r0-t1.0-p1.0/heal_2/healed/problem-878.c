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

    struct test_case
    {
        const char *label;
        const int *tuple;
        size_t size;
        size_t k;
    };

    struct test_case cases[] = {
        {"tuple1 contains exactly 6 elements", tuple1, size1, 6},
        {"tuple2 contains exactly 6 elements", tuple2, size2, 6},
        {"NULL tuple check", NULL, 0, 0}
    };

    size_t num_cases = sizeof(cases) / sizeof(cases[0]);

    for (size_t i = 0; i < num_cases; i++)
    {
        bool result = check_tuple_has_k_elements(cases[i].tuple,
                                                 cases[i].size,
                                                 cases[i].k);
        printf("%s: %s\n", cases[i].label, result ? "true" : "false");
    }

    return EXIT_SUCCESS;
}