#include <stdio.h>
#include <stdlib.h>

int is_linear(const int *seq, size_t n)
{
    size_t i;
    int diff;

    if (seq == NULL) {
        return 0;
    }

    if (n <= 2) {
        return 1;
    }

    diff = seq[1] - seq[0];

    for (i = 2; i < n; i++) {
        if (seq[i] - seq[i - 1] != diff) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    size_t n;
    size_t i;
    int *seq;
    int result;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input for size.\n");
        return EXIT_FAILURE;
    }

    if (n == 0 || n > 1000000) {
        fprintf(stderr, "Size out of allowed range.\n");
        return EXIT_FAILURE;
    }

    seq = malloc(n * sizeof(int));
    if (seq == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &seq[i]) != 1) {
            fprintf(stderr, "Invalid input for element %zu.\n", i);
            free(seq);
            return EXIT_FAILURE;
        }
    }

    result = is_linear(seq, n);

    if (result) {
        printf("The sequence is linear.\n");
    } else {
        printf("The sequence is not linear.\n");
    }

    free(seq);
    return EXIT_SUCCESS;
}