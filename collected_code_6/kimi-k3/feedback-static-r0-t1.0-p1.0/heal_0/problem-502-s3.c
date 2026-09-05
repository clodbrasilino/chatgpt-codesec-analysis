#include <stdio.h>

int find_remainder(int dividend, int divisor, int *remainder) {
    if (remainder == NULL) {
        return -1;
    }
    if (divisor == 0) {
        return -1;
    }
    *remainder = dividend % divisor;
    return 0;
}

int main(void) {
    int dividend = 0;
    int divisor = 0;
    int remainder = 0;
    int result = 0;

    printf("Enter dividend: ");
    if (scanf("%d", &dividend) != 1) {
        fprintf(stderr, "Invalid input for dividend.\n");
        return 1;
    }

    printf("Enter divisor: ");
    if (scanf("%d", &divisor) != 1) {
        fprintf(stderr, "Invalid input for divisor.\n");
        return 1;
    }

    result = find_remainder(dividend, divisor, &remainder);
    if (result != 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return 1;
    }

    printf("Remainder of %d divided by %d is %d\n", dividend, divisor, remainder);

    return 0;
}