#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_valid(const int *tup, size_t size)
{
    if (tup == NULL || size == 0U)
    {
        return false;
    }

    for (size_t i = 0U; i < size; i++)
    {
        if (tup[i] == 0)
        {
            return false;
        }
    }

    return true;
}

static void print_result(const char *label, const int *tup, size_t size)
{
    if (check_valid(tup, size))
    {
        (void)printf("%s: all values are valid\n", label);
    }
    else
    {
        (void)printf("%s: contains invalid values\n", label);
    }
}

int main(void)
{
    int tuple1[] = {1, 1, 1, 1};
    int tuple2[] = {1, 0, 1, 1};
    int tuple3[] = {1, 1, 1};

    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    print_result("Tuple 1", tuple1, size1);
    print_result("Tuple 2", tuple2, size2);
    print_result("Tuple 3", tuple3, size3);
    print_result("NULL tuple", NULL, 5U);

    return 0;
}