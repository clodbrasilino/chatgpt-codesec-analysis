#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_difference_of_two_squares(int64_t number)
{
    int64_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    int64_t number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *start = input;
    intmax_t value = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value < INT64_MIN || value > INT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (int64_t)value;
    puts(is_difference_of_two_squares(number) ? "Yes" : "No");

    return EXIT_SUCCESS;
}