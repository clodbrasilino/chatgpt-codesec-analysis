#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static bool is_decimal_with_precision_2(const char *text)
{
    if (text == NULL || *text == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    do {
        ++p;
    } while (isdigit(*p));

    if (*p++ != '.') {
        return false;
    }

    if (!isdigit(p[0]) || !isdigit(p[1])) {
        return false;
    }

    return p[2] == '\0';
}

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t length = 0;

    while (buffer[length] != '\0' &&
           buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\n' || buffer[length] == '\r') {
        int terminator = (unsigned char)buffer[length];
        buffer[length] = '\0';

        if (terminator == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return false;
                }
            } else if (next == EOF && ferror(stdin)) {
                return false;
            }
        }

        return true;
    }

    if (length < capacity - 1) {
        return true;
    }

    int ch = fgetc(stdin);

    if (ch == '\n') {
        return true;
    }

    if (ch == '\r') {
        int next = fgetc(stdin);
        if (next == '\n') {
            return true;
        }
        if (next == EOF) {
            return !ferror(stdin);
        }
        return false;
    }

    if (ch == EOF) {
        return !ferror(stdin);
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return false;
}

int main(void)
{
    char input[INPUT_SIZE];

    if (!read_line(input, sizeof input)) {
        puts("Invalid");
        return EXIT_FAILURE;
    }

    bool valid = is_decimal_with_precision_2(input);
    puts(valid ? "Valid" : "Invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}