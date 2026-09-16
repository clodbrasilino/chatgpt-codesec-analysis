#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool have_common_element(const int *list1, size_t len1, const int *list2, size_t len2)
{
    if (list1 == NULL || list2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        for (size_t j = 0; j < len2; j++) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int list_a[] = {1, 2, 3, 4, 5};
    int list_b[] = {9, 8, 7, 3};
    int list_c[] = {10, 20, 30};

    size_t len_a = sizeof(list_a) / sizeof(list_a[0]);
    size_t len_b = sizeof(list_b) / sizeof(list_b[0]);
    size_t len_c = sizeof(list_c) / sizeof(list_c[0]);

    if (have_common_element(list_a, len_a, list_b, len_b)) {
        if (printf("list_a and list_b share at least one element\n") < 0) {
            return 1;
        }
    } else {
        if (printf("list_a and list_b have no common elements\n") < 0) {
            return 1;
        }
    }

    if (have_common_element(list_a, len_a, list_c, len_c)) {
        if (printf("list_a and list_c share at least one element\n") < 0) {
            return 1;
        }
    } else {
        if (printf("list_a and list_c have no common elements\n") < 0) {
            return 1;
        }
    }

    return 0;
}