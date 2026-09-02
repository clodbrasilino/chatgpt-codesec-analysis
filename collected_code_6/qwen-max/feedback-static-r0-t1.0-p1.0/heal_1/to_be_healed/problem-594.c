#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findDifference(int *arr, int n) {
    int firstEven = INT_MAX, firstOdd = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0 && firstEven == INT_MAX) {
            firstEven = arr[i];
        } else if (arr[i] % 2 != 0 && firstOdd == INT_MAX) {
            firstOdd = arr[i];
        }
        if (firstEven != INT_MAX && firstOdd != INT_MAX) {
            break;
        }
    }
    if (firstEven == INT_MAX || firstOdd == INT_MAX) {
        return 0;
    }
    return firstEven - firstOdd;
}

int main() {
    int arr[] = {3, 6, 7, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findDifference(arr, n);
    printf("Difference: %d\n", result);
    return 0;
}