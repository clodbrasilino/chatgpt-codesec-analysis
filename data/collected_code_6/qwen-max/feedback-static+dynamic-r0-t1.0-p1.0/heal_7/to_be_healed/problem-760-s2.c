#include <stdio.h>
#include <stdbool.h>

bool isSingleDistinctElement(const int *arr, int len) {
    if (len <= 0) {
        return false;
    }
    if (len == 1) {
        return true;
    }

    for (int i = 1; i < len; ++i) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }

    return true;
}

int main() {
    const int arr1[] = {1, 1, 1, 1};
    const int arr2[] = {1, 2, 1, 1};
    const int arr3[] = {5};
    const int arr4[] = {};

    /* Possible weaknesses found:
     * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    printf(isSingleDistinctElement(arr1, 4) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    printf(isSingleDistinctElement(arr2, 4) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true
     *  Calling function 'isSingleDistinctElement' returns 1
     *  Condition 'isSingleDistinctElement(arr3,1)' is always true [knownConditionTrueFalse]
     */
    printf(isSingleDistinctElement(arr3, 1) ? "true\n" : "false\n");
    /* Possible weaknesses found:
     * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
     *  Condition 'isSingleDistinctElement(arr4,0)' is always false [knownConditionTrueFalse]
     *  Calling function 'isSingleDistinctElement' returns 0
     *  Condition 'isSingleDistinctElement(arr4,0)' is always false
     */
    printf(isSingleDistinctElement(arr4, 0) ? "true\n" : "false\n");

    return 0;
}