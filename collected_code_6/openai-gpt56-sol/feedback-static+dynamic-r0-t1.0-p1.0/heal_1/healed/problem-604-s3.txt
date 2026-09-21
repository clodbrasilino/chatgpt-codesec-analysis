#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

static void reverse_words(char *str, size_t length)
{
    char *current;
    char *end;

    if (str == NULL || length < 2U) {
        return;
    }

    end = str + length;
    reverse_range(str, end - 1);
    current = str;

    while (current < end) {
        char *word_start;

        while (current < end && *current == ' ') {
            ++current;
        }

        word_start = current;

        while (current < end && *current != ' ') {
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
    size_t text_length;
    ssize_t input_length;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    text_length = (size_t)input_length;

    if (text_length > 0U && line[text_length - 1U] == '\n') {
        --text_length;
        line[text_length] = '\0';

        if (text_length > 0U && line[text_length - 1U] == '\r') {
            --text_length;
            line[text_length] = '\0';
        }
    }

    reverse_words(line, text_length);

    if (fwrite(line, 1U, text_length, stdout) != text_length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}