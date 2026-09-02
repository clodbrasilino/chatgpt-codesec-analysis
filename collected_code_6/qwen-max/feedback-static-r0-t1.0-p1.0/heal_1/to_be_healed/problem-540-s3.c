#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findFreqDifference(int *arr, int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'count' can be reduced. [variableScope]
     */
    int maxCount = 0, minCount = INT_MAX, count;
    /* Possible weaknesses found:
     *  The scope of the variable 'maxVal' can be reduced. [variableScope]
     *  The scope of the variable 'minVal' can be reduced. [variableScope]
     */
    int maxVal, minVal;
    
    for (int i = 0; i < n; ++i) {
        count = 0;
        for (int j = 0; j < n; ++j) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            /* Possible weaknesses found:
             *  Value stored to 'maxVal' is never read [deadcode.DeadStores]
             *  Variable 'maxVal' is assigned a value that is never used. [unreadVariable]
             */
            maxVal = arr[i];
        }
        if (count < minCount && count != 0) {
            minCount = count;
            /* Possible weaknesses found:
             *  Value stored to 'minVal' is never read [deadcode.DeadStores]
             *  Variable 'minVal' is assigned a value that is never used. [unreadVariable]
             */
            minVal = arr[i];
        }
    }
    return maxCount - minCount;
}

int main() {
    int arr[] = {3, 5, 8, 2, 5, 3, 3, 5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = findFreqDifference(arr, n);
    printf("Difference between highest and least frequencies: %d\n", result);
    
    return 0;
}