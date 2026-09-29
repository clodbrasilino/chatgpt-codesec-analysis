#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_kth(int *arr, size_t size, size_t k) {
    if (arr == NULL || size == 0 || k >= size) {
        return -1;
    }
    return arr[k];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;
    int result = find_kth(arr, size, k);
    printf("%d\n", result);
    return 0;
}