#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_linear(const int *seq, size_t len) {
    if (seq == NULL) {
        if (len == 0) {
            return true;
        }
        return false;
    }

    if (len <= 2) {
        return true;
    }

    int first_diff = seq[1] - seq[0];

    for (size_t i = 2; i < len; i++) {
        if (seq[i] - seq[i - 1] != first_diff) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {1, 2, 4, 7};
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {5};
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    int arr4[] = {10, 20, 30, 40, 50};
    size_t len4 = sizeof(arr4) / sizeof(arr4[0]);

    bool res1 = is_linear(arr1, len1);
    bool res2 = is_linear(arr2, len2);
    bool res3 = is_linear(arr3, len3);
    bool res4 = is_linear(arr4, len4);
    /* Possible weaknesses found:
     *  Calling function 'is_linear' returns 0
     *  Assignment 'res5=is_linear(NULL,len1)', assigned value is 0
     */
    bool res5 = is_linear(NULL, len1);

    printf("Sequence 1 is linear: %s\n", res1 ? "true" : "false");
    printf("Sequence 2 is linear: %s\n", res2 ? "true" : "false");
    printf("Sequence 3 is linear: %s\n", res3 ? "true" : "false");
    printf("Sequence 4 is linear: %s\n", res4 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'res5' is always false
     *  Condition 'res5' is always false [knownConditionTrueFalse]
     */
    printf("Sequence 5 is linear: %s\n", res5 ? "true" : "false");

    return 0;
}