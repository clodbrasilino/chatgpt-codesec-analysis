#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;

    if (number < 100ULL) {
        return false;
    }

    first = (unsigned int)(number % 10ULL);
    number /= 10ULL;
    second = (unsigned int)(number % 10ULL);

    if (first == second) {
        return false;
    }

    number /= 10ULL;

    while (number != 0ULL) {
        unsigned int digit = (unsigned int)(number % 10ULL);

        if (digit != first) {
            return false;
        }

        first = second;
        second = digit;
        number /= 10ULL;
    }

    return true;
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length;
    int ch;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return true;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return false;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long number;

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}