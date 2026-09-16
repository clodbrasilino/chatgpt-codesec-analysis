#include <stdio.h>
#include <limits.h>

int countRotations(const int arr[], int n) {
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    const int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    /* Possible weaknesses found:
     *  'min_index' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'min_index'
     */
    int rotations = (min_index == 0) ? 0 : n - min_index;
    printf("Number of rotations: %d\n", rotations);
    return 0;
}