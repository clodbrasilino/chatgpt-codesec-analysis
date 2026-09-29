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

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < size && buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return 1;
}

int main(void)
{
    char input[256];
    char *cursor;
    char *end;
    long dividend;
    long divisor;
    int remainder;
    int status;

    status = read_line(input, sizeof input);
    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    dividend = strtol(cursor, &end, 10);
    if (cursor == end || errno == ERANGE ||
        dividend < INT_MIN || dividend > INT_MAX) {
        fputs("Invalid dividend.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    divisor = strtol(cursor, &end, 10);
    if (cursor == end || errno == ERANGE ||
        divisor < INT_MIN || divisor > INT_MAX) {
        fputs("Invalid divisor.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_remainder((int)dividend, (int)divisor, &remainder) != 0) {
        fputs("Divisor must not be zero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", remainder) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}