#include <stdio.h>
#include <stdlib.h>

enum { INPUT_SIZE = 1024 };

static int is_hex_digit(unsigned char character)
{
    return (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'f') ||
           (character >= (unsigned char)'A' &&
            character <= (unsigned char)'F');
}

static int is_hexadecimal(const char *text, size_t length)
{
    size_t index = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    if (length >= 2 &&
        text[0] == '0' &&
        (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
    }

    if (index == length) {
        return 0;
    }

    while (index < length) {
        if (!is_hex_digit((unsigned char)text[index])) {
            return 0;
        }
        ++index;
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)text[length - 1];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((digit - (unsigned char)'0') & 1U) == 0U;
    }

    if (digit >= (unsigned char)'A' && digit <= (unsigned char)'F') {
        digit = (unsigned char)(digit - (unsigned char)'A' +
                                (unsigned char)'a');
    }

    return (((unsigned int)(digit - (unsigned char)'a') + 10U) & 1U) == 0U;
}

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int character;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (used >= INPUT_SIZE) {
            free(buffer);
            return -2;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity > INPUT_SIZE + 1U) {
                new_capacity = INPUT_SIZE + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && used == 0) {
        free(buffer);
        return 0;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int status = read_line(&input, &length);

    if (status == 0) {
        fputs("No input\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == -2) {
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");
    free(input);
    return EXIT_SUCCESS;
}