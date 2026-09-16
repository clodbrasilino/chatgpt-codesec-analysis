#include <stdio.h>
#include <stdlib.h>

size_t count_self_modular_inverses(const int *arr, size_t size, int p) {
    if (arr == NULL || p <= 1) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        long long val = arr[i];
        long long mod_val = val % p;
        if (mod_val < 0) {
            mod_val += p;
        }
        
        if ((mod_val * mod_val) % p == 1) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int p = 11;
    
    size_t count = count_self_modular_inverses(arr, size, p);
    printf("%zu\n", count);
    
    return 0;
}