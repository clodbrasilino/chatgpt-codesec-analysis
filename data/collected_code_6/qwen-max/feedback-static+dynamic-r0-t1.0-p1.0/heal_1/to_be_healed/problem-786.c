#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findInsertPosition(int *arr, int n, int value) {
    int left = 0;
    int right = n - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int main() {
    int arr[] = {1, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 4;
    int position = findInsertPosition(arr, n, value);
    printf("The insertion point for %d is at index %d\n", value, position);
    return 0;
}