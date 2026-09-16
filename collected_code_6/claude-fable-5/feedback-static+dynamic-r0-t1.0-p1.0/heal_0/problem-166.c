#include <stdio.h>
#include <stdlib.h>

long long count_even_xor_pairs(const int *arr, size_t n)
{
    long long even_count = 0;
    long long odd_count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    return (even_count * (even_count - 1)) / 2 +
           (odd_count * (odd_count - 1)) / 2;
}

int main(void)
{
    int *arr = NULL;
    size_t n = 0;
    size_t i;
    long long result;

    printf("Enter number of elements: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > 1000000) {
        fprintf(stderr, "Invalid input for number of elements.\n");
        return EXIT_FAILURE;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid integer input.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    result = count_even_xor_pairs(arr, n);
    printf("Number of pairs with even XOR: %lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}