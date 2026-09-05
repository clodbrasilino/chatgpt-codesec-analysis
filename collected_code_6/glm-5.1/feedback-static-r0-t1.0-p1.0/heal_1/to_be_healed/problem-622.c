#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_median(int *arr, int n) {
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2;
    }
    return arr[n / 2];
}

int median_of_two_sorted_arrays(int *arr1, int *arr2, int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return (arr1[0] + arr2[0]) / 2;
    }
    if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;
    }

    int m1 = find_median(arr1, n);
    int m2 = find_median(arr2, n);

    if (m1 == m2) {
        return m1;
    }

    int new_n;
    int *new_arr1, *new_arr2;

    if (m1 < m2) {
        if (n % 2 == 0) {
            new_n = n - (n / 2 - 1);
            new_arr1 = arr1 + (n / 2 - 1);
            new_arr2 = arr2;
        } else {
            new_n = n - (n / 2);
            new_arr1 = arr1 + (n / 2);
            new_arr2 = arr2;
        }
    } else {
        if (n % 2 == 0) {
            new_n = n - (n / 2 - 1);
            new_arr1 = arr1;
            new_arr2 = arr2 + (n / 2 - 1);
        } else {
            new_n = n - (n / 2);
            new_arr1 = arr1;
            new_arr2 = arr2 + (n / 2);
        }
    }

    return median_of_two_sorted_arrays(new_arr1, new_arr2, new_n);
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr1)/sizeof(arr1[0])', assigned value is 5
     */
    int n = sizeof(arr1) / sizeof(arr1[0]);

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0 && sizeof(arr2) / sizeof(arr2[0]) == n) {
        int median = median_of_two_sorted_arrays(arr1, arr2, n);
        printf("%d\n", median);
    }

    return 0;
}