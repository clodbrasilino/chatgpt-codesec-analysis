#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096U

static int is_valid_triangle(double a, double b, double c)
{
    double largest;
    double other1;
    double other2;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    largest = a;
    other1 = b;
    other2 = c;

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

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    length = 0U;
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

    return discard_line() < 0 ? -1 : 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    double sides[3];
    char *cursor;
    int status;
    size_t i;

    status = read_line(input, sizeof input);

    if (status < 0) {
        fputs(ferror(stdin) ? "Input error\n" : "Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (i = 0U; i < 3U; ++i) {
        char *end;

        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        end = NULL;
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