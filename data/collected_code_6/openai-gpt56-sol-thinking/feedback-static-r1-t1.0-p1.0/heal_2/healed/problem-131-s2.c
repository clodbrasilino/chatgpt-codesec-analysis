#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    switch (character) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

static int reverse_vowels(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL) {
        return -1;
    }

    while (left < right) {
        while (left < right &&
               !is_vowel((unsigned char)string[left])) {
            ++left;
        }

        while (left < right &&
               !is_vowel((unsigned char)string[right - 1])) {
            --right;
        }

        if (left < right) {
            char temporary = string[left];
            string[left] = string[right - 1];
            string[right - 1] = temporary;
            ++left;
            --right;
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **output, size_t *output_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (stream == NULL || output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length] = (char)(unsigned char)character;
        ++length;
    }

    if (character == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;

    return 1;
}

int main(void)
{
    char *text = NULL;
    size_t text_length = 0;
    int status;

    status = read_line(stdin, &text, &text_length);
    if (status <= 0) {
        return EXIT_FAILURE;
    }

    if (reverse_vowels(text, text_length) != 0) {
        free(text);
        return EXIT_FAILURE;
    }

    if (fwrite(text, 1, text_length, stdout) != text_length ||
        fputc('\n', stdout) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}