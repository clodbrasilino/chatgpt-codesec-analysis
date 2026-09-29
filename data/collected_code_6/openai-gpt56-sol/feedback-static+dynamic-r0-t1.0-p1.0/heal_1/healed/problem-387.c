#include <ctype.h>
#include <stdio.h>

#define INPUT_CAPACITY 1024

static int is_hex_digit(unsigned char character)
{
    return (character >= '0' && character <= '9') ||
           (character >= 'a' && character <= 'f') ||
           (character >= 'A' && character <= 'F');
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length = 0;
    int character;

    if (buffer == NULL || capacity == 0) {
        return -1;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stdin)) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int is_hexadecimal(const char *text)
{
    size_t index = 0;

    if (text == NULL || text[0] == '\0') {
        return 0;
    }

    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
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
    const unsigned char *current = (const unsigned char *)text;
    unsigned char last_digit = '\0';

    while (*current != '\0') {
        last_digit = *current++;
    }

    return last_digit == '0' || last_digit == '2' ||
           last_digit == '4' || last_digit == '6' ||
           last_digit == '8' || last_digit == 'a' ||
           last_digit == 'c' || last_digit == 'e' ||
           last_digit == 'A' || last_digit == 'C' ||
           last_digit == 'E';
}

int main(void)
{
    char input[INPUT_CAPACITY];
    int status = read_line(input, sizeof input);

    if (status < 0) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (status == 0) {
        fputs("Input too long\n", stderr);
        return 1;
    }

    if (!is_hexadecimal(input)) {
        fputs("Invalid hexadecimal number\n", stderr);
        return 1;
    }

    puts(is_hex_even(input) ? "Even" : "Odd");
    return 0;
}