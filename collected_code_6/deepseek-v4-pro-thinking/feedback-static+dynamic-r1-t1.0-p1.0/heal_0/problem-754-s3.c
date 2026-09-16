#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int find_common_index_elements(const int *list1, size_t len1,
                               const int *list2, size_t len2,
                               const int *list3, size_t len3,
                               int *result, size_t result_capacity)
{
    size_t min_len;
    size_t i;
    size_t count;
    size_t pos;

    if ((len1 > 0 && list1 == NULL) ||
        (len2 > 0 && list2 == NULL) ||
        (len3 > 0 && list3 == NULL)) {
        return -1;
    }

    min_len = len1 < len2 ? len1 : len2;
    if (len3 < min_len) {
        min_len = len3;
    }

    if (min_len == 0) {
        return 0;
    }

    if (result == NULL && result_capacity > 0) {
        return -1;
    }

    count = 0;
    for (i = 0; i < min_len; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            count++;
        }
    }

    if (count > INT_MAX) {
        return -1;
    }

    if (count > result_capacity) {
        return -1;
    }

    pos = 0;
    for (i = 0; i < min_len; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            result[pos] = list1[i];
            pos++;
        }
    }

    return (int)count;
}

int main(void)
{
    int list1[] = { 1, 2, 3, 4, 5 };
    int list2[] = { 1, 2, 9, 4, 5 };
    int list3[] = { 1, 2, 3, 4, 0 };
    int common[5];
    int count;
    int i;

    count = find_common_index_elements(list1, 5, list2, 5, list3, 5,
                                       common, 5);

    if (count < 0) {
        printf("Error\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("%d ", common[i]);
    }
    printf("\n");

    return 0;
}