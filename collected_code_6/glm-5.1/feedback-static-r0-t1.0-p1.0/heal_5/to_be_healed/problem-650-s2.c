#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool arrays_equal(const int *arr1, size_t len1, const int *arr2, size_t len2) {
    if (arr1 == NULL && arr2 == NULL) {
        return true;
    }

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

    /* Possible weaknesses found:
     *  Condition 'arrays_equal(NULL,0,NULL,0)' is always true [knownConditionTrueFalse]
     *  Calling function 'arrays_equal' returns 1
     *  Condition 'arrays_equal(NULL,0,NULL,0)' is always true
     */
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