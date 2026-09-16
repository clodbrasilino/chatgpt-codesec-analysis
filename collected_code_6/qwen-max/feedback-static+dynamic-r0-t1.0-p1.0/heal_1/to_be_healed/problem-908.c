#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findFixedPoint(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {-10, -5, 0, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findFixedPoint(arr, n);
    if (result != -1) {
        printf("Fixed point is: %d\n", result);
    } else {
        printf("No fixed point found.\n");
    }
    return 0;
}