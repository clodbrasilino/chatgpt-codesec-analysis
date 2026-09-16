#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_three_lowest_positive(int *arr, int size) {
    int first = INT_MAX, second = INT_MAX, third = INT_MAX;
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
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
    }
    
    if (count < 3) {
        return -1;
    }
    
    return first + second + third;
}

int main(void) {
    int arr1[] = {5, 2, 8, 1, 9, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int result1 = sum_three_lowest_positive(arr1, size1);
    if (result1 != -1) {
        printf("Sum of three lowest positive numbers: %d\n", result1);
    } else {
        printf("Not enough positive numbers in the array\n");
    }
    
    int arr2[] = {-1, 4, 2, 0, 3};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int result2 = sum_three_lowest_positive(arr2, size2);
    if (result2 != -1) {
        printf("Sum of three lowest positive numbers: %d\n", result2);
    } else {
        printf("Not enough positive numbers in the array\n");
    }
    
    int arr3[] = {1, -2, -3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int result3 = sum_three_lowest_positive(arr3, size3);
    if (result3 != -1) {
        printf("Sum of three lowest positive numbers: %d\n", result3);
    } else {
        printf("Not enough positive numbers in the array\n");
    }
    
    int arr4[] = {10, 20, 30};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    int result4 = sum_three_lowest_positive(arr4, size4);
    if (result4 != -1) {
        printf("Sum of three lowest positive numbers: %d\n", result4);
    } else {
        printf("Not enough positive numbers in the array\n");
    }
    
    return 0;
}