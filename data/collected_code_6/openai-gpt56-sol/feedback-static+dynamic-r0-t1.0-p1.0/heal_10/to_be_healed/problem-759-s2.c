#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096U

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= (unsigned char)'0' && *p <= (unsigned char)'9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != (unsigned char)'.') {
        return false;
    }

    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }
    ++p;

    if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
        return false;
    }
    ++p;

    return *p == (unsigned char)'\0';
}

static bool read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return length > 0U;
    }

    {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_line(input, INPUT_SIZE)) {
        fputs("Input error\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}