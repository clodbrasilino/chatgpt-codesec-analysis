#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_three_lowest_positive(int *arr, int size) {
    int first = INT_MAX, second = INT_MAX, third = INT_MAX;
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] <= 0) {
            continue;
        }

        count++;

        if (arr[i] < first) {
            third = second;
            second = first;
            first = arr[i];
        } else if (arr[i] < second) {
            third = second;
            second = arr[i];
        } else if (arr[i] < third) {
            third = arr[i];
        }
    }

    if (count < 3) {
        return -1;
    }

    return first + second + third;
}

int main(void) {
    int arr1[] = {3, 7, 1, -2, 9, 4, -6, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = sum_three_lowest_positive(arr1, size1);
    printf("Result 1: %d\n", result1);

    int arr2[] = {-5, -10, 0, 2, 8};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = sum_three_lowest_positive(arr2, size2);
    printf("Result 2: %d\n", result2);

    int arr3[] = {5, 4, 3, 2, 1};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = sum_three_lowest_positive(arr3, size3);
    printf("Result 3: %d\n", result3);

    int arr4[] = {-1, -2, -3};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int result4 = sum_three_lowest_positive(arr4, size4);
    printf("Result 4: %d\n", result4);

    return 0;
}