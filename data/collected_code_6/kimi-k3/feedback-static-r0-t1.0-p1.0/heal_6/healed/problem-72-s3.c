#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

bool isDifferenceOfSquares(int n)
{
    if (n == INT_MIN) {
        return false;
    }
    if (n < 0) {
        n = -n;
    }
    return (n % 4 != 2);
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    char *endptr;
    long val;
    int num;

    printf("Enter a number: ");
    
    line_length = getline(&buffer, &buffer_size, stdin);
    if (line_length == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Input out of range.\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    num = (int)val;

    if (isDifferenceOfSquares(num)) {
        printf("%d can be represented as difference of two squares.\n", num);
    } else {
        printf("%d cannot be represented as difference of two squares.\n", num);
    }

    free(buffer);
    return EXIT_SUCCESS;
}