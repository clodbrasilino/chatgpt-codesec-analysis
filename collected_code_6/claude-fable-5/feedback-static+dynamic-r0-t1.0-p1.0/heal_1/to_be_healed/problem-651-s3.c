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

int main(void)
{
    int main_tuple[] = {10, 4, 5, 6, 7};
    int sub_tuple[] = {5, 10};
    int not_sub_tuple[] = {5, 10, 99};

    size_t main_len = sizeof(main_tuple) / sizeof(main_tuple[0]);
    size_t sub_len = sizeof(sub_tuple) / sizeof(sub_tuple[0]);
    size_t not_sub_len = sizeof(not_sub_tuple) / sizeof(not_sub_tuple[0]);

    if (is_subset(main_tuple, main_len, sub_tuple, sub_len)) {
        printf("Tuple {5, 10} is a subset of the main tuple.\n");
    } else {
        printf("Tuple {5, 10} is not a subset of the main tuple.\n");
    }

    if (is_subset(main_tuple, main_len, not_sub_tuple, not_sub_len)) {
        printf("Tuple {5, 10, 99} is a subset of the main tuple.\n");
    } else {
        printf("Tuple {5, 10, 99} is not a subset of the main tuple.\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'is_subset' returns 1
     *  Condition 'is_subset(main_tuple,main_len,NULL,0)' is always true [knownConditionTrueFalse]
     *  Condition 'is_subset(main_tuple,main_len,NULL,0)' is always true
     */
    if (is_subset(main_tuple, main_len, NULL, 0)) {
        printf("Empty tuple is a subset of the main tuple.\n");
    } else {
        printf("Empty tuple is not a subset of the main tuple.\n");
    }

    return EXIT_SUCCESS;
}