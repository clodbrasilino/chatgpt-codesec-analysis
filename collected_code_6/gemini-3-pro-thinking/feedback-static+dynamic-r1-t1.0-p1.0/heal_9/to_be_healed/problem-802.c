#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

size_t count_rotations(const int *arr, size_t n) {
    if (!arr || n == 0) {
        return 0;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        if (arr[low] < arr[high]) {
            break;
        }

        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return low;
}

int main(void) {
    unsigned long n_in;
    
    while (scanf("%lu", &n_in) == 1) {
        size_t n = (size_t)n_in;
        if (n == 0) {
            printf("0\n");
            continue;
        }
        
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr) {
            for (size_t i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            
            printf("%lu\n", (unsigned long)count_rotations(arr, n));
            free(arr);
        }
    }

    return 0;
}