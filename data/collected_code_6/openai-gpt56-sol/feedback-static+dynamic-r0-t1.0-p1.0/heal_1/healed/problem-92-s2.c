#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (number == 0ULL) {
        return false;
    }

    unsigned int second = (unsigned int)(number % 10ULL);
    number /= 10ULL;

    if (first == second) {
        return false;
    }

    bool expect_first = true;

    while (number != 0ULL) {
        unsigned int digit = (unsigned int)(number % 10ULL);

        if (digit != (expect_first ? first : second)) {
            return false;
        }

        expect_first = !expect_first;
        number /= 10ULL;
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    free(input);
    return EXIT_SUCCESS;
}