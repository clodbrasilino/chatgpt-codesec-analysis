#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int find_remainder(int dividend, int divisor, int *remainder)
{
    if (remainder == NULL || divisor == 0) {
        return -1;
    }

    if (dividend == INT_MIN && divisor == -1) {
        *remainder = 0;
        return 0;
    }

    *remainder = dividend % divisor;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *cursor;
    char *end;
    long dividend;
    long divisor;
    int remainder;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    cursor = input;
    errno = 0;
    dividend = strtol(cursor, &end, 10);
    if (cursor == end || errno == ERANGE ||
        dividend < INT_MIN || dividend > INT_MAX) {
        fputs("Invalid dividend.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    divisor = strtol(cursor, &end, 10);
    if (cursor == end || errno == ERANGE ||
        divisor < INT_MIN || divisor > INT_MAX) {
        fputs("Invalid divisor.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (find_remainder((int)dividend, (int)divisor, &remainder) != 0) {
        fputs("Divisor must not be zero.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    printf("%d\n", remainder);
    free(input);
    return EXIT_SUCCESS;
}