#include <ctype.h>
#include <errno.h>
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

static bool read_number(unsigned long long *number)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end;

    if (number == NULL) {
        return false;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    errno = 0;
    *number = strtoull(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    free(line);
    return true;
}

int main(void)
{
    unsigned long long number;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    return EXIT_SUCCESS;
}