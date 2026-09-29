#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_difference_of_two_squares(int64_t number)
{
    return number % 4 != 2 && number % 4 != -2;
}

int main(void)
{
    char input[128];
    char *end;
    intmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE || value < INT64_MIN || value > INT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n",
           is_difference_of_two_squares((int64_t)value) ? "Yes" : "No");

    return EXIT_SUCCESS;
}