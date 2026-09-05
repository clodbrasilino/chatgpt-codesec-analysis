#include <stdio.h>
#include <stdlib.h>

int max_sum_no_adjacent(int *arr, int n) {
    if (arr == NULL) {
        return 0;
    }
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return arr[0] > 0 ? arr[0] : 0;
    }

    long long inclusive = arr[0] > 0 ? arr[0] : 0;
    long long exclusive = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_exclusive' can be reduced. [variableScope]
     */
    long long new_exclusive;

    for (int i = 1; i < n; i++) {
        new_exclusive = inclusive > exclusive ? inclusive : exclusive;
        inclusive = exclusive + (arr[i] > 0 ? arr[i] : 0);
        exclusive = new_exclusive;
    }

    long long result = inclusive > exclusive ? inclusive : exclusive;
    if (result > (long long)0x7FFFFFFF) {
        result = (long long)0x7FFFFFFF;
    }
    if (result < 0) {
        result = 0;
    }

    return (int)result;
}

int main(void) {
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", max_sum_no_adjacent(arr1, n1));

    int arr2[] = {3, 2, 7, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", max_sum_no_adjacent(arr2, n2));

    int arr3[] = {-1, -2, -3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", max_sum_no_adjacent(arr3, n3));

    printf("%d\n", max_sum_no_adjacent(NULL, 5));

    return 0;
}