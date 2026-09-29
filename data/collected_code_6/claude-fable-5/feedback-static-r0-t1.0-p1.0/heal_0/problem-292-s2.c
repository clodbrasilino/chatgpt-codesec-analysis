#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_quotient(int dividend, int divisor, int *result)
{
    if (divisor == 0) {
        return -1;
    }
    if (dividend == INT_MIN && divisor == -1) {
        return -1;
    }
    *result = dividend / divisor;
    return 0;
}

int main(void)
{
    int a;
    int b;
    int quotient;

    printf("Enter dividend: ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Invalid input for dividend\n");
        return EXIT_FAILURE;
    }

    printf("Enter divisor: ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid input for divisor\n");
        return EXIT_FAILURE;
    }

    if (find_quotient(a, b, &quotient) != 0) {
        fprintf(stderr, "Error: division cannot be performed\n");
        return EXIT_FAILURE;
    }

    printf("Quotient: %d\n", quotient);
    return EXIT_SUCCESS;
}