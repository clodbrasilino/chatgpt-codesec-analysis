#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long count_odd_xor_pairs(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    long long even_count = 0;
    long long odd_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }
    
    return even_count * odd_count;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    
    long long result = count_odd_xor_pairs(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}