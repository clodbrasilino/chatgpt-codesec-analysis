#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                fputs("Input error\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n' || ch == '\r') {
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(input);
                fputs("Input too long\n", stderr);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation error\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';
    puts(frequencies_are_valid(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}