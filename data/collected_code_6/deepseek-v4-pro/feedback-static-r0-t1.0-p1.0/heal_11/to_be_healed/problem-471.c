#include <stdio.h>
#include <stdbool.h>

bool findRemainder(const int arr[], int size, int n, int *result) {
    if (size <= 0 || n == 0 || result == NULL) {
        return false;
    }

    int remainder = 1 % n;

    for (int i = 0; i < size; i++) {
        remainder = (remainder * (arr[i] % n)) % n;
    }

    *result = remainder;
    return true;
}

int main() {
    int arr1[] = {100, 10, 5, 25, 35, 14};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int n1 = 11;
    int result1;

    if (findRemainder(arr1, size1, n1, &result1)) {
        printf("Remainder of array multiplication divided by %d is %d\n", n1, result1);
    } else {
        printf("Invalid input\n");
    }

    int arr2[] = {2, 3, 4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int n2 = 5;
    int result2;

    if (findRemainder(arr2, size2, n2, &result2)) {
        printf("Remainder of array multiplication divided by %d is %d\n", n2, result2);
    } else {
        printf("Invalid input\n");
    }

    int arr3[] = {5, 7, 9, 11};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int n3 = 2;
    int result3;

    if (findRemainder(arr3, size3, n3, &result3)) {
        printf("Remainder of array multiplication divided by %d is %d\n", n3, result3);
    } else {
        printf("Invalid input\n");
    }

    int arr4[] = {1, 2, 3};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int n4 = 0;
    int result4;

    /* Possible weaknesses found:
     *  Condition 'findRemainder(arr4,size4,n4,&result4)' is always false
     *  Condition 'findRemainder(arr4,size4,n4,&result4)' is always false [knownConditionTrueFalse]
     *  Calling function 'findRemainder' returns 0
     */
    if (findRemainder(arr4, size4, n4, &result4)) {
        printf("Remainder of array multiplication divided by %d is %d\n", n4, result4);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}