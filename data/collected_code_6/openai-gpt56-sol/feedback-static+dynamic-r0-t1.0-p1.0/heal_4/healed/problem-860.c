#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    const unsigned char *cursor;
    unsigned char last = 0;

    if (string == NULL || result == NULL) {
        return -1;
    }

    cursor = (const unsigned char *)string;

    while (*cursor != '\0') {
        last = *cursor++;
    }

    *result = (last >= (unsigned char)'0' && last <= (unsigned char)'9') ||
              (last >= (unsigned char)'A' && last <= (unsigned char)'Z') ||
              (last >= (unsigned char)'a' && last <= (unsigned char)'z');

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;

    return 0;
}

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length >= capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return NULL;
            }
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    bool result;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        fputs("Input processing failed.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(result ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}