#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_fixed_point(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {-10, -5, 0, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int fixed_point = find_fixed_point(arr, n);
    if (fixed_point != -1) {
        printf("Fixed point is: %d\n", fixed_point);
    } else {
        printf("No fixed point found.\n");
    }
    return 0;
}