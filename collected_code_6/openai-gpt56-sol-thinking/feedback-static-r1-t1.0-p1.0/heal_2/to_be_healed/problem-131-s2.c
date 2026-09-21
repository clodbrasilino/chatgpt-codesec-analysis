#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    return character == 'a' || character == 'e' ||
           character == 'i' || character == 'o' ||
           character == 'u' || character == 'A' ||
           character == 'E' || character == 'I' ||
           character == 'O' || character == 'U';
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length >= capacity - 1) {
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
    *output_length = length;

    return 1;
}

int main(void)
{
    char *text = NULL;
    size_t text_length = 0;
    int read_status;

    read_status = read_line(stdin, &text, &text_length);
    if (read_status <= 0) {
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