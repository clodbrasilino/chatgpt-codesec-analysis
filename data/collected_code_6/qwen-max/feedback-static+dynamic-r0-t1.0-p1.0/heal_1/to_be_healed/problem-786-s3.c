#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_insertion_point(int *arr, int size, int value) {
    int left = 0;
    int right = size - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int main() {
    int arr[] = {1, 3, 5, 6, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int value = 7;
    int index = find_insertion_point(arr, size, value);
    printf("Insert at index: %d\n", index);
    return 0;
}