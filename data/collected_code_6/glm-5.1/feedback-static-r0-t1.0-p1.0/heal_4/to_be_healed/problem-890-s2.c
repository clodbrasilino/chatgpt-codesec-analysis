#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main() {
    const int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    const int arr2[] = {2, 4, 6, 8, 10, 12};
    /* Possible weaknesses found:
     *  Assignment 'n1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 7
     */
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    /* Possible weaknesses found:
     *  Assignment 'n2=sizeof(arr2)/sizeof(arr2[0])', assigned value is 6
     */
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    /* Possible weaknesses found:
     *  Condition 'n1<=0' is always false
     *  Condition 'n2<=0' is always false
     *  Condition 'n2<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n1<=0' is always false [knownConditionTrueFalse]
     */
    if (n1 <= 0 || n2 <= 0) {
        return EXIT_FAILURE;
    }

    const int *longer_arr;
    const int *shorter_arr;
    int longer_n;

    /* Possible weaknesses found:
     *  Condition 'n1>n2' is always true [knownConditionTrueFalse]
     *  Condition 'n1>n2' is always true
     */
    if (n1 > n2) {
        longer_arr = arr1;
        shorter_arr = arr2;
        longer_n = n1;
    } else if (n2 > n1) {
        longer_arr = arr2;
        shorter_arr = arr1;
        longer_n = n2;
    } else {
        return EXIT_FAILURE;
    }

    int index = find_extra_element_index(longer_arr, shorter_arr, longer_n);
    printf("%d\n", index);

    return EXIT_SUCCESS;
}