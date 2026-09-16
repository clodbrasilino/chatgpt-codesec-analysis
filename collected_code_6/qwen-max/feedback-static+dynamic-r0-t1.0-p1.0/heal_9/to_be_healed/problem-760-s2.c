#include <stdio.h>
#include <stdbool.h>

bool isSingleDistinctElement(const int *arr, int len) {
    if (len != 1) {
        return false;
    }

    return true;
}

int main() {
    const int arr1[] = {1, 1, 1, 1};
    const int arr2[] = {1, 2, 1, 1};
    const int arr3[] = {5};
    const int arr4[] = {};

    /* Possible weaknesses found:
     *  Calling function 'isSingleDistinctElement' returns 0
     *  Condition 'isSingleDistinctElement(arr1,4)' is always false [knownConditionTrueFalse]
     *  Condition 'isSingleDistinctElement(arr1,4)' is always false
     */
    printf(isSingleDistinctElement(arr1, 4) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     *  Calling function 'isSingleDistinctElement' returns 0
     *  Condition 'isSingleDistinctElement(arr2,4)' is always false [knownConditionTrueFalse]
     *  Condition 'isSingleDistinctElement(arr2,4)' is always false
     */
    printf(isSingleDistinctElement(arr2, 4) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true [knownConditionTrueFalse]
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true
     *  Calling function 'isSingleDistinctElement' returns 1
     */
    printf(isSingleDistinctElement(arr3, 1) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     *  Condition 'isSingleDistinctElement(arr4,0)' is always false [knownConditionTrueFalse]
     *  Calling function 'isSingleDistinctElement' returns 0
     *  Condition 'isSingleDistinctElement(arr4,0)' is always false
     */
    printf(isSingleDistinctElement(arr4, 0) ? "true\n" : "false\n");

    return 0;
}