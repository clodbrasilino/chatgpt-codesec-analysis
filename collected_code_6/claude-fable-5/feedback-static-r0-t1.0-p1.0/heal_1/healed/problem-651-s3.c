#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_subset(const int *tuple_a, size_t len_a, const int *tuple_b, size_t len_b)
{
    if (tuple_b == NULL || len_b == 0) {
        return true;
    }
    if (tuple_a == NULL || len_a == 0) {
        return false;
    }

    for (size_t i = 0; i < len_b; i++) {
        bool found = false;
        for (size_t j = 0; j < len_a; j++) {
            if (tuple_b[i] == tuple_a[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

struct test_case {
    const char *label;
    const int *tuple;
    size_t len;
};

int main(void)
{
    int main_tuple[] = {10, 4, 5, 6, 7};
    int sub_tuple[] = {5, 10};
    int not_sub_tuple[] = {5, 10, 99};

    size_t main_len = sizeof(main_tuple) / sizeof(main_tuple[0]);

    struct test_case cases[] = {
        {"Tuple {5, 10}", sub_tuple, sizeof(sub_tuple) / sizeof(sub_tuple[0])},
        {"Tuple {5, 10, 99}", not_sub_tuple, sizeof(not_sub_tuple) / sizeof(not_sub_tuple[0])},
        {"Empty tuple", NULL, 0}
    };

    size_t num_cases = sizeof(cases) / sizeof(cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        bool result = is_subset(main_tuple, main_len, cases[i].tuple, cases[i].len);
        printf("%s is %sa subset of the main tuple.\n",
               cases[i].label,
               result ? "" : "not ");
    }

    return EXIT_SUCCESS;
}