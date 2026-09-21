#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 1024U

static int is_hex_digit(unsigned char character)
{
    return (character >= (unsigned char)'0' &&
            character <= (unsigned char)'9') ||
           (character >= (unsigned char)'a' &&
            character <= (unsigned char)'f') ||
           (character >= (unsigned char)'A' &&
            character <= (unsigned char)'F');
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? -1 : 0;
    }

    for (length = 0U; buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 1;
        }
    }

    if (feof(stdin)) {
        return 1;
    }

    {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        buffer[0] = '\0';

        if (ferror(stdin)) {
            return -1;
        }
    }

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
    size_t index = 0U;
    unsigned char last_digit;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    while (text[index + 1U] != '\0') {
        ++index;
    }

    last_digit = (unsigned char)text[index];

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
    char *input;
    int status;
    int result;

    input = malloc(INPUT_CAPACITY * sizeof(*input));

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_line(input, INPUT_CAPACITY);

    if (status < 0) {
        fputs("Input error\n", stderr);
        result = EXIT_FAILURE;
    } else if (status == 0) {
        fputs("Input too long or unavailable\n", stderr);
        result = EXIT_FAILURE;
    } else if (!is_hexadecimal(input)) {
        fputs("Invalid hexadecimal number\n", stderr);
        result = EXIT_FAILURE;
    } else {
        puts(is_hex_even(input) ? "Even" : "Odd");
        result = EXIT_SUCCESS;
    }

    free(input);
    return result;
}