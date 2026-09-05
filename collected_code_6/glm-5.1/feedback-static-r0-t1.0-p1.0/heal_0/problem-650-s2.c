#include <stdio.h>
#include <stdlib.h>

int arrays_equal(int *arr1, size_t len1, int *arr2, size_t len2) {
    if (arr1 == NULL || arr2 == NULL) {
        if (arr1 == NULL && arr2 == NULL) {
            return 1;
        }
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    for (size_t i = 0; i < len1; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 3, 4, 0};
    size_t len_a = sizeof(a) / sizeof(a[0]);
    size_t len_b = sizeof(b) / sizeof(b[0]);
    size_t len_c = sizeof(c) / sizeof(c[0]);

    if (arrays_equal(a, len_a, b, len_b)) {
        printf("a and b are equal\n");
    } else {
        printf("a and b are not equal\n");
    }

    if (arrays_equal(a, len_a, c, len_c)) {
        printf("a and c are equal\n");
    } else {
        printf("a and c are not equal\n");
    }

    if (arrays_equal(NULL, 0, NULL, 0)) {
        printf("Two NULL arrays are equal\n");
    } else {
        printf("Two NULL arrays are not equal\n");
    }

    if (arrays_equal(a, len_a, NULL, 0)) {
        printf("a and NULL are equal\n");
    } else {
        printf("a and NULL are not equal\n");
    }

    return 0;
}