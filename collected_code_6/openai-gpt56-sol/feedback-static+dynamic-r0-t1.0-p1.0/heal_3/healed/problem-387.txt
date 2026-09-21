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
    size_t length;

    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return ferror(stdin) ? -1 : 1;
    }

    length = 0U;
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

    for (;;) {
        int character = getchar();

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stdin)) {
                buffer[0] = '\0';
                return -1;
            }
            break;
        }
    }

    buffer[0] = '\0';
    return 0;
}

static int is_hexadecimal(const char *text)
{
    size_t index = 0U;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
        index = 2U;
    }

    if (text[index] == '\0') {
        return 0;
    }

    while (text[index] != '\0') {
        if (!is_hex_digit((unsigned char)text[index])) {
            return 0;
        }
        ++index;
    }

    return 1;
}

static int is_hex_even(const char *text)
{
    size_t length;
    unsigned char last_digit;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    length = 0U;
    while (text[length] != '\0') {
        ++length;
    }

    last_digit = (unsigned char)text[length - 1U];

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
    char input[INPUT_CAPACITY];
    int status = read_line(input, sizeof input);

    if (status < 0) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fputs("Input too long\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_hexadecimal(input)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_hex_even(input) ? "Even" : "Odd");
    return EXIT_SUCCESS;
}