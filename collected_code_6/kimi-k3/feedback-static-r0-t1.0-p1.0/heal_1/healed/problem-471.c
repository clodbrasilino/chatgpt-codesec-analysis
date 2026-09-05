#include <stdio.h>
#include <stdlib.h>

int find_remainder(const int arr[], int size, int n) {
    if (n == 0) {
        return -1;
    }
    long long result = 1;
    for (int i = 0; i < size; i++) {
        result = (result * arr[i]) % n;
    }
    return (int)result;
}

int main() {
    int size, n;
    
    if (scanf("%d", &size) != 1 || size <= 0) {
        return 1;
    }
    
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    
    if (scanf("%d", &n) != 1 || n == 0) {
        free(arr);
        return 1;
    }
    
    int remainder = find_remainder(arr, size, n);
    printf("%d\n", remainder);
    
    free(arr);
    return 0;
}