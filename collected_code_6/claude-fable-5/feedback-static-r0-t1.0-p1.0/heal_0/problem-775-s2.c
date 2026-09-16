#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool odd_indices_contain_odd(const int *arr, size_t len)
{
    size_t i;

    if (arr == NULL) {
        return false;
    }

    for (i = 1U; i < len; i += 2U) {
        if ((arr[i] % 2) == 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list1[] = {2, 1, 4, 3, 6, 7};
    int list2[] = {2, 1, 4, 3, 6, 7, 8, 8};
    int list3[] = {1, 2, 3};
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t len3 = sizeof(list3) / sizeof(list3[0]);

    if (odd_indices_contain_odd(list1, len1)) {
        (void)printf("list1: true\n");
    } else {
        (void)printf("list1: false\n");
    }

    if (odd_indices_contain_odd(list2, len2)) {
        (void)printf("list2: true\n");
    } else {
        (void)printf("list2: false\n");
    }

    if (odd_indices_contain_odd(list3, len3)) {
        (void)printf("list3: true\n");
    } else {
        (void)printf("list3: false\n");
    }

    return 0;
}