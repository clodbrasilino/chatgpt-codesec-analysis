#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int is_space(char character)
{
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r' || character == '\f' || character == '\v';
}

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

static void reverse_words(char *string)
{
    if (string == NULL) {
        return;
    }

    size_t length = strlen(string);

    if (length < 2U) {
        return;
    }

    reverse_range(string, string + length - 1U);

    char *current = string;

    while (*current != '\0') {
        while (is_space(*current)) {
            ++current;
        }

        char *word_start = current;

        while (*current != '\0' && !is_space(*current)) {
            ++current;
        }

        if (word_start < current) {
            reverse_range(word_start, current - 1);
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        int status = ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';

        if (length > 0 && line[length - 1] == '\r') {
            line[length - 1] = '\0';
        }
    }

    reverse_words(line);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}