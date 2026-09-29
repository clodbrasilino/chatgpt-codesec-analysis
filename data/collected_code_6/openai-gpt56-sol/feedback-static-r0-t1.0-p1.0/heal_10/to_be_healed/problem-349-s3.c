#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        ++str;
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
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

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = length + 1;
    }

    input[length] = '\0';

    int result = fputs(is_binary_string(input)
                           ? "Binary string\n"
                           : "Not a binary string\n",
                       stdout);

    free(input);
    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}