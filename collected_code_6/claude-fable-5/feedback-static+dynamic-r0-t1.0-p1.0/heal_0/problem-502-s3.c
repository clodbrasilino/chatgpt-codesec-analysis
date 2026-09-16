#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor, int *result)
{
    if (divisor == 0) {
        return -1;
    }
    *result = dividend % divisor;
    return 0;
}

int main(void)
{
    int a;
    int b;
    int remainder;

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

    if (find_remainder(a, b, &remainder) != 0) {
        fprintf(stderr, "Error: division by zero is not allowed\n");
        return EXIT_FAILURE;
    }

    printf("Remainder of %d %% %d = %d\n", a, b, remainder);

    return EXIT_SUCCESS;
}