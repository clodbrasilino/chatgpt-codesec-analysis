#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char input[128];
    char *start;
    char *end;
    char *newline;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}