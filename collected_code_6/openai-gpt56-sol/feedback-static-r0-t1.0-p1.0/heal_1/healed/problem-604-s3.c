#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
    }
}

static void reverse_words(char *str, size_t length)
{
    char *current;
    char *limit;

    if (str == NULL || length < 2U) {
        return;
    }

    reverse_range(str, str + length - 1U);

    current = str;
    limit = str + length;

    while (current < limit) {
        char *word_start;

        while (current < limit && *current == ' ') {
            ++current;
        }

        word_start = current;

        while (current < limit && *current != ' ') {
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
    size_t content_length;
    ssize_t input_length;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    content_length = (size_t)input_length;

    if (content_length > 0U && line[content_length - 1U] == '\n') {
        --content_length;
        line[content_length] = '\0';

        if (content_length > 0U && line[content_length - 1U] == '\r') {
            --content_length;
            line[content_length] = '\0';
        }
    }

    reverse_words(line, content_length);

    if (fwrite(line, 1U, content_length, stdout) != content_length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}