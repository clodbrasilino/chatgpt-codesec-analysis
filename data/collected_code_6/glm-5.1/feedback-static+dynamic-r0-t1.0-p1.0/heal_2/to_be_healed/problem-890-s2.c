#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (mid < n - 1 && arr1[mid] == arr2[mid]) {
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
     *  Assignment 'ptr1=arr1', assigned value is {
     */
    const int *ptr1 = arr1;
    /* Possible weaknesses found:
     *  Assignment 'ptr2=arr2', assigned value is {
     */
    const int *ptr2 = arr2;
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr1)/sizeof(arr1[0])', assigned value is 7
     */
    int n = sizeof(arr1) / sizeof(arr1[0]);

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'ptr1==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'ptr2==NULL' is always false
     *  Condition 'ptr1==NULL' is always false
     *  Condition 'ptr2==NULL' is always false [knownConditionTrueFalse]
     */
    if (n <= 0 || ptr1 == NULL || ptr2 == NULL) {
        return EXIT_FAILURE;
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    return EXIT_SUCCESS;
}