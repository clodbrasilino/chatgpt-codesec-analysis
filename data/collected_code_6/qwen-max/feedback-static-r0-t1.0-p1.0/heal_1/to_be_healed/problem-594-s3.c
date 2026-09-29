#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findDifference(int *arr, int size) {
    int firstEven = -1, firstOdd = -1;
    for (int i = 0; i < size; ++i) {
        if (firstEven == -1 && arr[i] % 2 == 0) {
            firstEven = arr[i];
        }
        if (firstOdd == -1 && arr[i] % 2 != 0) {
            firstOdd = arr[i];
        }
        if (firstEven != -1 && firstOdd != -1) break;
    }
    return (firstEven != -1 && firstOdd != -1) ? firstEven - firstOdd : -1;
}

int main() {
    int arr[] = {3, 7, 2, 8, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findDifference(arr, size);
    if (result != -1) {
        printf("The difference is: %d\n", result);
    } else {
        printf("Not enough even and odd numbers in the list.\n");
    }
    return 0;
}