#include <stdio.h>

int count_odd(const int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 != 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = count_odd(arr, n);
    printf("Number of odd elements: %d\n", result);

    int test1[] = {1, 3, 5, 7};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    int result1 = count_odd(test1, n1);
    printf("Number of odd elements: %d\n", result1);

    int test2[] = {2, 4, 6, 8};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    int result2 = count_odd(test2, n2);
    printf("Number of odd elements: %d\n", result2);

    int test3[] = {1, 2, 3, 4};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    int result3 = count_odd(test3, n3);
    printf("Number of odd elements: %d\n", result3);

    return 0;
}