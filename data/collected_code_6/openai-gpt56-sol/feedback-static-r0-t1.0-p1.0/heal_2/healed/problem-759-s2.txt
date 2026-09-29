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

static bool discard_remaining_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);

    return !ferror(stdin);
}

int main(void)
{
    char input[INPUT_SIZE];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return 1;
        }

        input[0] = '\0';
    } else {
        size_t length = 0;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else if (length == sizeof input - 1) {
            int character = getchar();

            if (character != '\n' && character != EOF) {
                if (!discard_remaining_line()) {
                    fputs("Input error\n", stderr);
                    return 1;
                }

                fputs("Input too long\n", stderr);
                return 1;
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return 1;
            }
        }
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return 0;
}