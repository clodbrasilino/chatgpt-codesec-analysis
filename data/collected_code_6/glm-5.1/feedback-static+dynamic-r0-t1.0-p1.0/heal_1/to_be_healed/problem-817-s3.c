#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void find_divisible(int *arr, size_t size, int m, int n) {
    if (m == 0 || n == 0) {
        return;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % m == 0 || arr[i] % n == 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main(void) {
    int m = 3;
    int n = 5;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    find_divisible(arr, size, m, n);
    
    return 0;
}