#include <stdio.h>
#include <stdlib.h>

int arithmetic_progression_nth_term(int first_term, int common_difference, int n) {
    if (n < 1) {
        fprintf(stderr, "Error: Term position must be positive\n");
        exit(EXIT_FAILURE);
    }
    return first_term + (n - 1) * common_difference;
}

int main(void) {
    int first_term;
    int common_difference;
    int n;
    int result;

    printf("Enter first term: ");
    if (scanf("%d", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference: ");
    if (scanf("%d", &common_difference) != 1) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    printf("Enter term position: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for term position\n");
        return EXIT_FAILURE;
    }

    result = arithmetic_progression_nth_term(first_term, common_difference, n);
    printf("The %d-th term is: %d\n", n, result);

    return EXIT_SUCCESS;
}