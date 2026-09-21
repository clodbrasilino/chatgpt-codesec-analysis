#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;
    size_t digit_count = 0U;
    unsigned long long value = number;

    if (number < 100ULL) {
        return false;
    }

    first = (unsigned int)(value % 10ULL);
    value /= 10ULL;
    second = (unsigned int)(value % 10ULL);

    if (first == second) {
        return false;
    }

    while (value != 0ULL) {
        unsigned int digit = (unsigned int)(value % 10ULL);
        unsigned int expected = (digit_count % 2U == 0U) ? first : second;

        if (digit != expected) {
            return false;
        }

        ++digit_count;
        value /= 10ULL;
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end;
    unsigned long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    free(input);
    return EXIT_SUCCESS;
}