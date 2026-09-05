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
    const int arr[] = {1, 2, 3, 4, 5, 6};
    const int sub1[] = {3, 4, 5};
    const int sub2[] = {1, 2};
    const int sub3[] = {5, 6};
    const int sub4[] = {7, 8};
    const int sub5[] = {};
    const int sub6[] = {2, 4};

    printf("%d\n", is_subarray(arr, 6, sub1, 3));
    printf("%d\n", is_subarray(arr, 6, sub2, 2));
    printf("%d\n", is_subarray(arr, 6, sub3, 2));
    printf("%d\n", is_subarray(arr, 6, sub4, 2));
    printf("%d\n", is_subarray(arr, 6, sub5, 0));
    printf("%d\n", is_subarray(arr, 6, sub6, 2));

    return 0;
}