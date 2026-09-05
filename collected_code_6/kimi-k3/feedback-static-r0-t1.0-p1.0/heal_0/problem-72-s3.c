#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

bool isDifferenceOfSquares(int n)
{
    if (n < 0) {
        n = -n;
    }
    return (n % 4 != 2);
}

int main(void)
{
    int num;
    char buffer[256];
    char *endptr;
    long val;

    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    num = (int)val;

    if (isDifferenceOfSquares(num)) {
        printf("%d can be represented as difference of two squares.\n", num);
    } else {
        printf("%d cannot be represented as difference of two squares.\n", num);
    }

    return EXIT_SUCCESS;
}