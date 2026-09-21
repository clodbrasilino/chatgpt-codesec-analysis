#include <stdbool.h>
#include <stdio.h>

#define INPUT_SIZE 256

static bool is_decimal_with_precision_2(const char *text)
{
    size_t i = 0;
    size_t integer_digits = 0;

    if (text == NULL || text[0] == '\0') {
        return false;
    }

    if (text[i] == '+' || text[i] == '-') {
        ++i;
    }

    while (text[i] >= '0' && text[i] <= '9') {
        ++integer_digits;
        ++i;
    }

    if (integer_digits == 0 || text[i] != '.') {
        return false;
    }

    ++i;

    if (text[i] < '0' || text[i] > '9') {
        return false;
    }

    ++i;

    if (text[i] < '0' || text[i] > '9') {
        return false;
    }

    ++i;

    return text[i] == '\0';
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t length = 0;
    int character;

    while (length + 1 < sizeof input) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (length + 1 == sizeof input) {
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return 1;
            }

            fputs("Input too long\n", stderr);
            return 1;
        }
    }

    input[length] = '\0';

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}