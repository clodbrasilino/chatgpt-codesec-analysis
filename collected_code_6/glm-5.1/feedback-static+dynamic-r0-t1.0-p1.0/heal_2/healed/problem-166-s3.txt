#include <stdio.h>
#include <stdlib.h>

long long count_even_xor_pairs(const int *arr, int n) {
    long long even_count = 0;
    long long odd_count = 0;
    long long i;

    if (arr == NULL || n < 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    return (even_count * (even_count - 1) / 2) + (odd_count * (odd_count - 1) / 2);
}

int main(int argc, char * const argv[]) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    if (argc > 1) {
        n = argc - 1;
        int *dyn_arr = (int *)malloc(n * sizeof(int));
        if (dyn_arr == NULL) {
            return EXIT_FAILURE;
        }

        for (int i = 0; i < n; i++) {
            dyn_arr[i] = atoi(argv[i + 1]);
        }

        result = count_even_xor_pairs(dyn_arr, n);
        printf("%lld\n", result);

        free(dyn_arr);
    } else {
        result = count_even_xor_pairs(arr, n);
        printf("%lld\n", result);
    }

    return EXIT_SUCCESS;
}