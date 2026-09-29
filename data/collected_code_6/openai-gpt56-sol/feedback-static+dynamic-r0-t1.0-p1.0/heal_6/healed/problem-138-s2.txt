#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static bool is_sum_of_nonzero_powers_of_two(unsigned long long number)
{
    return number != 0ULL && (number & (number - 1ULL)) == 0ULL;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(line);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    puts(is_sum_of_nonzero_powers_of_two(number) ? "True" : "False");

    free(line);
    return EXIT_SUCCESS;
}