#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_kth_element(int *arr, int n, int k) {
    if (k < 0 || k >= n) {
        return -1;
    }
    return arr[k];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = find_kth_element(arr, n, k);
    if (result != -1) {
        printf("The %dth element is: %d\n", k + 1, result);
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}