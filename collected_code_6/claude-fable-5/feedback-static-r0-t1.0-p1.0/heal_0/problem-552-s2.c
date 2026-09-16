#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_linear(const long *seq, size_t n)
{
    size_t i;
    long diff;

    if (seq == NULL) {
        return false;
    }
    if (n <= 2) {
        return true;
    }
    diff = seq[1] - seq[0];
    for (i = 2; i < n; i++) {
        if (seq[i] - seq[i - 1] != diff) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    size_t n;
    size_t i;
    long *seq;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input for size\n");
        return EXIT_FAILURE;
    }
    if (n == 0 || n > 1000000) {
        fprintf(stderr, "Size out of allowed range\n");
        return EXIT_FAILURE;
    }

    seq = malloc(n * sizeof(*seq));
    if (seq == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%ld", &seq[i]) != 1) {
            fprintf(stderr, "Invalid input for element %zu\n", i);
            free(seq);
            return EXIT_FAILURE;
        }
    }

    if (is_linear(seq, n)) {
        printf("The sequence is linear\n");
    } else {
        printf("The sequence is not linear\n");
    }

    free(seq);
    return EXIT_SUCCESS;
}