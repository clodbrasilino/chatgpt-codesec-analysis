#include <stdio.h>
#include <stdbool.h>

bool is_subarray(const int *arr, size_t arr_len, const int *sub, size_t sub_len) {
    if (sub_len == 0) {
        return true;
    }
    if (arr == NULL || sub == NULL || sub_len > arr_len) {
        return false;
    }
    size_t limit = arr_len - sub_len;
    for (size_t i = 0; i <= limit; i++) {
        bool match = true;
        for (size_t j = 0; j < sub_len; j++) {
            if (arr[i + j] != sub[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr' can be declared as const array [constVariable]
     */
    int arr[] = {1, 2, 3, 4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'sub1' can be declared as const array [constVariable]
     */
    int sub1[] = {3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'sub2' can be declared as const array [constVariable]
     */
    int sub2[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'sub3' can be declared as const array [constVariable]
     */
    int sub3[] = {5, 6};
    /* Possible weaknesses found:
     *  Variable 'sub4' can be declared as const array [constVariable]
     */
    int sub4[] = {7, 8};
    /* Possible weaknesses found:
     *  Variable 'sub5' can be declared as const array [constVariable]
     */
    int sub5[] = {};
    /* Possible weaknesses found:
     *  Variable 'sub6' can be declared as const array [constVariable]
     */
    int sub6[] = {2, 4};

    printf("%d\n", is_subarray(arr, 6, sub1, 3));
    printf("%d\n", is_subarray(arr, 6, sub2, 2));
    printf("%d\n", is_subarray(arr, 6, sub3, 2));
    printf("%d\n", is_subarray(arr, 6, sub4, 2));
    printf("%d\n", is_subarray(arr, 6, sub5, 0));
    printf("%d\n", is_subarray(arr, 6, sub6, 2));

    return 0;
}