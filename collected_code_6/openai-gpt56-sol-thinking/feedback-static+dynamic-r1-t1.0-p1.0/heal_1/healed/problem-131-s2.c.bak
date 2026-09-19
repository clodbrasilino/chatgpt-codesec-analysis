#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_vowel(unsigned char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int reverse_vowels(char *str)
{
    size_t left;
    size_t right;

    if (str == NULL) {
        return -1;
    }

    left = 0;
    right = strlen(str);

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)str[left])) {
            ++left;
        }

        while (left < right && !is_vowel((unsigned char)str[right - 1])) {
            --right;
        }

        if (left < right) {
            char temporary = str[left];
            str[left] = str[right - 1];
            str[right - 1] = temporary;
            ++left;
            --right;
        }
    }

    return 0;
}

static int read_line(FILE *stream, char **output)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            char *resized_buffer;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized_buffer = realloc(buffer, new_capacity);

            if (resized_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
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
    return 1;
}

int main(void)
{
    char *text = NULL;
    int read_status = read_line(stdin, &text);

    if (read_status <= 0) {
        return EXIT_FAILURE;
    }

    if (reverse_vowels(text) != 0) {
        free(text);
        return EXIT_FAILURE;
    }

    if (fputs(text, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}