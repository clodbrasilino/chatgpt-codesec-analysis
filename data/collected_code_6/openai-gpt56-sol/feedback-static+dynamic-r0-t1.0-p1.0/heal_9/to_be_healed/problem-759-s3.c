#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool is_decimal_with_precision_2(const char *text)
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

    while (isdigit(*p)) {
        ++p;
    }

    if (*p != '.') {
        return false;
    }
    ++p;

    if (!isdigit(*p)) {
        return false;
    }
    ++p;

    if (!isdigit(*p)) {
        return false;
    }
    ++p;

    return *p == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (capacity != 0 && capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity <= length + 1) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        --length;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = length + 1;
    }

    input[length] = '\0';

    bool valid = is_decimal_with_precision_2(input);
    free(input);

    puts(valid ? "Valid" : "Invalid");
    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}