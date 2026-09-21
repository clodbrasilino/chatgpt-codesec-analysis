#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 1024U

static int is_hex_digit(unsigned char character)
{
    return (character >= (unsigned char)'0' && character <= (unsigned char)'9') ||
           (character >= (unsigned char)'a' && character <= (unsigned char)'f') ||
           (character >= (unsigned char)'A' && character <= (unsigned char)'F');
}

static int read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return ferror(stdin) ? -1 : 1;
    }

    size_t length = 0U;
    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    int character;
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    if (ferror(stdin)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';
    return 0;
}

static int is_hexadecimal(const char *text)
{
    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    size_t index = 0U;

    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
        index = 2U;
    }

    if (text[index] == '\0') {
        return 0;
    }

    for (; text[index] != '\0'; ++index) {
        if (!is_hex_digit((unsigned char)text[index])) {
            return 0;
        }
    }

    return 1;
}

static int is_hex_even(const char *text)
{
    const unsigned char *current = (const unsigned char *)text;
    unsigned char last_digit = '\0';

    if (current == NULL) {
        return 0;
    }

    while (*current != '\0') {
        last_digit = *current;
        ++current;
    }

    return last_digit == (unsigned char)'0' ||
           last_digit == (unsigned char)'2' ||
           last_digit == (unsigned char)'4' ||
           last_digit == (unsigned char)'6' ||
           last_digit == (unsigned char)'8' ||
           last_digit == (unsigned char)'a' ||
           last_digit == (unsigned char)'c' ||
           last_digit == (unsigned char)'e' ||
           last_digit == (unsigned char)'A' ||
           last_digit == (unsigned char)'C' ||
           last_digit == (unsigned char)'E';
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    int status = read_line(input, INPUT_CAPACITY);

    if (status < 0) {
        fputs("Input error\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Input too long\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (!is_hexadecimal(input)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input) ? "Even" : "Odd");
    free(input);
    return EXIT_SUCCESS;
}