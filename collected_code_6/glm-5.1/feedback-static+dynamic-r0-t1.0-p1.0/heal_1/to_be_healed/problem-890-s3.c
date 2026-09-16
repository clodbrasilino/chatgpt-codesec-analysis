#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (mid < n - 1 && arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {1, 2, 3, 5, 6};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int index = find_extra_element_index(arr1, arr2, n);

    printf("%d\n", index);

    return 0;
}