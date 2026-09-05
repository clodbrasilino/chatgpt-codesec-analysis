#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
int find_extra_element_index(int *arr1, int *arr2, int n) {
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

int main() {
    int arr1[] = {2, 4, 6, 8, 10, 12, 13};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr1)/sizeof(arr1[0])', assigned value is 7
     */
    int n = sizeof(arr1) / sizeof(arr1[0]);

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'arr2==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'arr1==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0 || arr1 == NULL || arr2 == NULL) {
        return EXIT_FAILURE;
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    return EXIT_SUCCESS;
}