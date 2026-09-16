#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool arrays_equal(const int *arr1, size_t len1, const int *arr2, size_t len2)
{
    if (arr1 == NULL || arr2 == NULL) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 3, 4, 6};
    int d[] = {1, 2, 3};

    size_t len_a = sizeof(a) / sizeof(a[0]);
    size_t len_b = sizeof(b) / sizeof(b[0]);
    size_t len_c = sizeof(c) / sizeof(c[0]);
    size_t len_d = sizeof(d) / sizeof(d[0]);

    if (arrays_equal(a, len_a, b, len_b)) {
        printf("Arrays a and b are equal\n");
    } else {
        printf("Arrays a and b are not equal\n");
    }

    if (arrays_equal(a, len_a, c, len_c)) {
        printf("Arrays a and c are equal\n");
    } else {
        printf("Arrays a and c are not equal\n");
    }

    if (arrays_equal(a, len_a, d, len_d)) {
        printf("Arrays a and d are equal\n");
    } else {
        printf("Arrays a and d are not equal\n");
    }

    return 0;
}