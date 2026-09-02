#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

int list_to_int(const int *arr, size_t count, int *result) {
    if (arr == NULL || result == NULL || count == 0) {
        return -1;
    }

    long long temp = 0;
    int sign = 1;
    size_t i = 0;

    if (arr[0] < 0) {
        sign = -1;
        temp = -(long long)arr[0];
        i = 1;
        if (count == 1) {
            if (arr[0] < INT_MIN) {
                return -1;
            }
            *result = arr[0];
            return 0;
        }
    } else {
        temp = arr[0];
        i = 1;
    }

    for (; i < count; i++) {
        if (arr[i] < 0 || arr[i] > 9) {
            return -1;
        }
        if (temp > (LLONG_MAX - arr[i]) / 10) {
            return -1;
        }
        temp = temp * 10 + arr[i];
    }

    temp *= sign;

    if (temp > INT_MAX || temp < INT_MIN) {
        return -1;
    }

    *result = (int)temp;
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int result1;
    if (list_to_int(arr1, 5, &result1) == 0) {
        printf("%d\n", result1);
    } else {
        printf("Error\n");
    }

    int arr2[] = {-1, 2, 3};
    int result2;
    if (list_to_int(arr2, 3, &result2) == 0) {
        printf("%d\n", result2);
    } else {
        printf("Error\n");
    }

    int arr3[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    int result3;
    if (list_to_int(arr3, 11, &result3) == 0) {
        printf("%d\n", result3);
    } else {
        printf("Error\n");
    }

    int arr4[] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
    int result4;
    if (list_to_int(arr4, 10, &result4) == 0) {
        printf("%d\n", result4);
    } else {
        printf("Error\n");
    }

    int arr5[] = {-2, 1, 4, 7, 4, 8, 3, 6, 4, 8};
    int result5;
    if (list_to_int(arr5, 10, &result5) == 0) {
        printf("%d\n", result5);
    } else {
        printf("Error\n");
    }

    int arr6[] = {10, 2};
    int result6;
    if (list_to_int(arr6, 2, &result6) == 0) {
        printf("%d\n", result6);
    } else {
        printf("Error\n");
    }

    int arr7[] = {-1};
    int result7;
    if (list_to_int(arr7, 1, &result7) == 0) {
        printf("%d\n", result7);
    } else {
        printf("Error\n");
    }

    return 0;
}