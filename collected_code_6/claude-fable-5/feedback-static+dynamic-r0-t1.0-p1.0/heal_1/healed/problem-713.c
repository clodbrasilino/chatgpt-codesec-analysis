#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_valid(const int *tuple, size_t size)
{
    if (tuple == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == 0) {
            return false;
        }
    }

    return true;
}

static void print_result(bool result)
{
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

int main(void)
{
    int tuple1[] = {1, 1, 1, 1};
    int tuple2[] = {1, 0, 1, 1};
    int tuple3[] = {1, 1, 1};

    struct test_case {
        const int *tuple;
        size_t size;
    };

    struct test_case cases[] = {
        { tuple1, sizeof(tuple1) / sizeof(tuple1[0]) },
        { tuple2, sizeof(tuple2) / sizeof(tuple2[0]) },
        { tuple3, sizeof(tuple3) / sizeof(tuple3[0]) },
        { NULL, 0 }
    };

    size_t num_cases = sizeof(cases) / sizeof(cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        print_result(check_valid(cases[i].tuple, cases[i].size));
    }

    return 0;
}