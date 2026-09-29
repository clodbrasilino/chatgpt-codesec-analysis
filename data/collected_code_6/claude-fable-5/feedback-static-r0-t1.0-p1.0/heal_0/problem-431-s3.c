#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool has_common_element(const int *list1, size_t len1, const int *list2, size_t len2)
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
    int list_a[] = {1, 3, 5, 7, 9};
    int list_b[] = {2, 4, 6, 8, 9};
    int list_c[] = {10, 20, 30};

    size_t len_a = sizeof(list_a) / sizeof(list_a[0]);
    size_t len_b = sizeof(list_b) / sizeof(list_b[0]);
    size_t len_c = sizeof(list_c) / sizeof(list_c[0]);

    if (has_common_element(list_a, len_a, list_b, len_b)) {
        if (printf("List A and List B share at least one element.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("List A and List B share no elements.\n") < 0) {
            return 1;
        }
    }

    if (has_common_element(list_a, len_a, list_c, len_c)) {
        if (printf("List A and List C share at least one element.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("List A and List C share no elements.\n") < 0) {
            return 1;
        }
    }

    return 0;
}