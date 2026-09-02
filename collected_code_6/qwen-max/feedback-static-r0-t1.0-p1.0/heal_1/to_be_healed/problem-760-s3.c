#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isSingleDistinctElement(int arr[], int n) {
    if (n <= 1) {
        return true;
    }
    for (int i = 1; i < n; ++i) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr1[] = {5, 5, 5, 5};
    int arr2[] = {5, 6, 5, 5};
    int arr3[] = {7};
    int arr4[] = {};

    printf("%s\n", isSingleDistinctElement(arr1, 4) ? "true" : "false");
    printf("%s\n", isSingleDistinctElement(arr2, 4) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true [knownConditionTrueFalse]
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true
     *  Calling function 'isSingleDistinctElement' returns 1
     */
    printf("%s\n", isSingleDistinctElement(arr3, 1) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'isSingleDistinctElement(arr4,0)' is always true
     *  Calling function 'isSingleDistinctElement' returns 1
     *  Condition 'isSingleDistinctElement(arr4,0)' is always true [knownConditionTrueFalse]
     */
    printf("%s\n", isSingleDistinctElement(arr4, 0) ? "true" : "false");

    return 0;
}