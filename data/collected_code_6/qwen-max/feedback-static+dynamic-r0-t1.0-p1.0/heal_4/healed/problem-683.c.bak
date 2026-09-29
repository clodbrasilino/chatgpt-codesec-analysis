#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int isSumOfTwoSquares(long n) {
    if (n < 0)
        return 0;
    for (long i = 0; i * i <= n; ++i) {
        long j = lround(sqrt(n - i * i));
        if (i * i + j * j == n && j * j == (n - i * i)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char input[256];
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        errno = 0;
        long n = strtol(input, &endptr, 10);
        if (errno == ERANGE || *endptr != '\n' || endptr == input) {
            printf("Invalid input.\n");
            return 1;
        }
        if (isSumOfTwoSquares(n)) {
            printf("The number can be represented as the sum of two squares.\n");
        } else {
            printf("The number cannot be represented as the sum of two squares.\n");
        }
    } else {
        printf("Error reading input.\n");
        return 1;
    }
    return 0;
}