#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t digit_distance(intmax_t first, intmax_t second)
{
    uintmax_t left = magnitude(first);
    uintmax_t right = magnitude(second);
    uintmax_t distance = 0;

    do {
        uintmax_t left_digit = left % UINTMAX_C(10);
        uintmax_t right_digit = right % UINTMAX_C(10);

        distance += left_digit >= right_digit
                        ? left_digit - right_digit
                        : right_digit - left_digit;

        left /= UINTMAX_C(10);
        right /= UINTMAX_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    first = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;

    if (!isspace((unsigned char)*cursor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    second = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}