#include <stdio.h>
#include <stdlib.h>

int max_sum_non_adjacent(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    if (n == 1) {
        return arr[0] > 0 ? arr[0] : 0;
    }

    int incl = arr[0] > 0 ? arr[0] : 0;
    int excl = 0;
    int excl_new;

    for (size_t i = 1; i < n; i++) {
        excl_new = (incl > excl) ? incl : excl;
        incl = excl + arr[i];
        excl = excl_new;
    }

    return (incl > excl) ? incl : excl;
}

int main(void) {
    int arr[] = {3, 2, 7, 10};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int max_sum = max_sum_non_adjacent(arr, n);
    
    printf("Maximum sum: %d\n", max_sum);

    return EXIT_SUCCESS;
}