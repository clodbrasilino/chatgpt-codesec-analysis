#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_smaller(const int *tuple1, const int *tuple2, size_t length)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || length == 0U) {
        return false;
    }

    for (i = 0; i < length; i++) {
        if (tuple2[i] >= tuple1[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first1[] = {1, 2, 3};
    const int second1[] = {0, 1, 2};
    const int first2[] = {4, 5, 6};
    const int second2[] = {5, 4, 3};
    size_t len1 = sizeof(first1) / sizeof(first1[0]);
    size_t len2 = sizeof(first2) / sizeof(first2[0]);

    if (check_smaller(first1, second1, len1)) {
        printf("Test 1: True\n");
    } else {
        printf("Test 1: False\n");
    }

    if (check_smaller(first2, second2, len2)) {
        printf("Test 2: True\n");
    } else {
        printf("Test 2: False\n");
    }

    return 0;
}