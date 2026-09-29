#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Input error\n", stderr);
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == sizeof input - 1) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Input too long\n", stderr);
        return 1;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}