#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_numeric_values(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str) != 0) {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    char *line = NULL;
    size_t capacity = 0;

    while (getline(&line, &capacity, stdin) != -1) {
        count += count_numeric_values(line);
    }

    if (ferror(stdin) != 0) {
        fprintf(stderr, "Failed to read input.\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}