#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int remove_non_alphanumeric(char *string)
{
    unsigned char *source;
    char *destination;

    if (string == NULL) {
        return -1;
    }

    source = (unsigned char *)string;
    destination = string;

    while (*source != '\0') {
        if (isalnum(*source)) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
    return 0;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[128];

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }

            if (length == 0) {
                free(input);
                return EXIT_SUCCESS;
            }

            break;
        }

        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                goto input_complete;
            }

            if (length == capacity - 1) {
                size_t new_capacity;
                char *new_input;

                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
                new_input = realloc(input, new_capacity);

                if (new_input == NULL) {
                    free(input);
                    return EXIT_FAILURE;
                }

                input = new_input;
                capacity = new_capacity;
            }

            input[length++] = buffer[i];
        }
    }

input_complete:
    input[length] = '\0';

    if (remove_non_alphanumeric(input) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}