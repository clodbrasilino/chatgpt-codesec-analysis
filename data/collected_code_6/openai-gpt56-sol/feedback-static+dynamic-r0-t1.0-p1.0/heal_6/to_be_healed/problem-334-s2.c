#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static int is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    double largest = a;
    double other1 = b;
    double other2 = c;

    if (b > largest) {
        largest = b;
        other1 = a;
        other2 = c;
    }

    if (c > largest) {
        largest = c;
        other1 = a;
        other2 = b;
    }

    return largest - other1 < other2;
}

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    size_t length = 0;

    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length < size && buffer[length] == '\0' && feof(stdin)) {
        return 1;
    }

    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    if (ferror(stdin)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    int status = read_line(input, sizeof input);

    if (status < 0) {
        fputs(ferror(stdin) ? "Input error\n" : "Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    double sides[3];
    char *cursor = input;

    for (size_t i = 0; i < 3; ++i) {
        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        char *end = NULL;
        errno = 0;
        sides[i] = strtod(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(sides[i])) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        cursor = end;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_valid_triangle(sides[0], sides[1], sides[2])
             ? "Valid triangle"
             : "Invalid triangle");

    return EXIT_SUCCESS;
}