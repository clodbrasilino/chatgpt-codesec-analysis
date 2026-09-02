#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findFixedPoint(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {-10, -5, 0, 3, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int fixedPoint = findFixedPoint(arr, size);

    if (fixedPoint != -1) {
        printf("Fixed point found at index %d\n", fixedPoint);
    } else {
        printf("No fixed point found\n");
    }

    return 0;
}