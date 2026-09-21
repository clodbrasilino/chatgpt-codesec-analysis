#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void capitalize_first_and_last(char *string, size_t length)
{
    size_t index = 0;

    while (index < length) {
        while (index < length && isspace((unsigned char)string[index])) {
            ++index;
        }

        if (index == length) {
            break;
        }

        size_t first = index;

        while (index < length && !isspace((unsigned char)string[index])) {
            ++index;
        }

        size_t last = index - 1;
        string[first] = (char)toupper((unsigned char)string[first]);
        string[last] = (char)toupper((unsigned char)string[last]);
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t result = getline(&line, &capacity, stdin);

    if (result < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    size_t length = (size_t)result;

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';

        if (length > 0 && line[length - 1] == '\r') {
            line[--length] = '\0';
        }
    }

    capitalize_first_and_last(line, length);

    if (fwrite(line, 1, length, stdout) != length || fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}