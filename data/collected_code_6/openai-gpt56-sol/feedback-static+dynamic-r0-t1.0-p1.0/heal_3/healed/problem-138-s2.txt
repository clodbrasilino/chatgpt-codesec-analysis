#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_nonzero_powers_of_two(unsigned long long number)
{
    return number >= 3ULL && (number & (number - 1ULL)) != 0ULL;
}

int main(void)
{
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_nonzero_powers_of_two(number) ? "True" : "False");
    return EXIT_SUCCESS;
}