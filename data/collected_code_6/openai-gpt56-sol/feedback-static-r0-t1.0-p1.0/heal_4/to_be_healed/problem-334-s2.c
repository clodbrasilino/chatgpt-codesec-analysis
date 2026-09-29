#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    return a > fabs(b - c) && a < b + c;
}

static int discard_remaining_input(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *cursor;
    char *end;
    double sides[3];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_remaining_input();
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (size_t i = 0; i < 3; ++i) {
        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        sides[i] = strtod(cursor, &end);

        if (end == cursor || errno == ERANGE) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        cursor = end;
    }

    while (isspace((unsigned char)*cursor)) {
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