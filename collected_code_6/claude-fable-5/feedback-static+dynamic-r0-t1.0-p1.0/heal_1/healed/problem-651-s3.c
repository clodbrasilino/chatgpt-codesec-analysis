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

static void report_subset(const char *label, const int *tuple_a, size_t len_a,
                          const int *tuple_b, size_t len_b)
{
    bool result = is_subset(tuple_a, len_a, tuple_b, len_b);
    if (result) {
        printf("%s is a subset of the main tuple.\n", label);
    } else {
        printf("%s is not a subset of the main tuple.\n", label);
    }
}

int main(void)
{
    int main_tuple[] = {10, 4, 5, 6, 7};
    int sub_tuple[] = {5, 10};
    int not_sub_tuple[] = {5, 10, 99};

    size_t main_len = sizeof(main_tuple) / sizeof(main_tuple[0]);
    size_t sub_len = sizeof(sub_tuple) / sizeof(sub_tuple[0]);
    size_t not_sub_len = sizeof(not_sub_tuple) / sizeof(not_sub_tuple[0]);

    struct {
        const char *label;
        const int *tuple;
        size_t len;
    } tests[] = {
        { "Tuple {5, 10}", sub_tuple, sub_len },
        { "Tuple {5, 10, 99}", not_sub_tuple, not_sub_len },
        { "Empty tuple", NULL, 0 }
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        report_subset(tests[i].label, main_tuple, main_len,
                      tests[i].tuple, tests[i].len);
    }

    return EXIT_SUCCESS;
}