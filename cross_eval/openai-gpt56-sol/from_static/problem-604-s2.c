#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int is_separator(char character)
{
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r' || character == '\f' || character == '\v';
}

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
    }
}

static void reverse_words(char *string, size_t length)
{
    char *current;
    char *end;

    if (string == NULL || length < 2U) {
        return;
    }

    reverse_range(string, string + length - 1U);

    current = string;
    end = string + length;

    while (current < end) {
        char *word_start;

        while (current < end && is_separator(*current)) {
            ++current;
        }

        word_start = current;

        while (current < end && !is_separator(*current)) {
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
    ssize_t input_length = getline(&line, &capacity, stdin);

    if (input_length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return status;
    }

    size_t length = (size_t)input_length;

    if (length > 0U && line[length - 1U] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0U && line[length - 1U] == '\r') {
        line[--length] = '\0';
    }

    reverse_words(line, length);

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}