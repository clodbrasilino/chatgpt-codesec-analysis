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

static void report_tuple(const char *name, const int *tup, size_t size)
{
    if (check_valid(tup, size))
    {
        (void)printf("%s: all values are valid\n", name);
    }
    else
    {
        (void)printf("%s: contains invalid values\n", name);
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

    report_tuple("Tuple 1", tuple1, size1);
    report_tuple("Tuple 2", tuple2, size2);
    report_tuple("Tuple 3", tuple3, size3);

    return 0;
}