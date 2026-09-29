#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static int is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    return a > fabs(b - c) && c > a - b;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid input\n", stderr);
        }
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    double sides[3];
    char *cursor = input;

    for (size_t i = 0; i < 3; ++i) {
        char *end;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        errno = 0;
        sides[i] = strtod(cursor, &end);

        if (end == cursor || errno == ERANGE || !isfinite(sides[i])) {
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