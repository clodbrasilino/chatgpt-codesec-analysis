#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void capitalize_word_boundaries(char *string, size_t length)
{
    if (string == NULL) {
        return;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char current = (unsigned char)string[i];

        if (isspace(current)) {
            continue;
        }

        if (i == 0U || isspace((unsigned char)string[i - 1U])) {
            string[i] = (char)toupper(current);
        }

        if (i + 1U == length || isspace((unsigned char)string[i + 1U])) {
            string[i] = (char)toupper((unsigned char)string[i]);
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t result = getline(&line, &capacity, stdin);

    if (result < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    size_t length = (size_t)result;

    if (length > 0U && line[length - 1U] == '\n') {
        line[--length] = '\0';

        if (length > 0U && line[length - 1U] == '\r') {
            line[--length] = '\0';
        }
    }

    capitalize_word_boundaries(line, length);

    if (fwrite(line, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}