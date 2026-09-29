#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr2' can be declared as const array [constParameter]
 *  Parameter 'arr1' can be declared as const array [constParameter]
 */
int findExtraElementIndex(int arr1[], int arr2[], int n) {
    int left = 0;
    int right = n - 1;
    int index = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr1[mid] == arr2[mid]) {
            left = mid + 1;
        } else {
            index = mid;
            right = mid - 1;
        }
    }

    return index;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    int arr2[] = {1, 2, 3, 5, 6, 7};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr2)/sizeof(arr2[0])', assigned value is 6
     */
    int n = sizeof(arr2) / sizeof(arr2[0]);

    /* Possible weaknesses found:
     *  Condition 'n<0' is always false [knownConditionTrueFalse]
     *  Condition 'n<0' is always false
     */
    if (n < 0 || (sizeof(arr1) / sizeof(arr1[0])) != n + 1) {
        printf("Invalid input arrays.\n");
        return 1;
    }

    int index = findExtraElementIndex(arr1, arr2, n);
    
    printf("Index of the extra element is: %d\n", index);

    return 0;
}