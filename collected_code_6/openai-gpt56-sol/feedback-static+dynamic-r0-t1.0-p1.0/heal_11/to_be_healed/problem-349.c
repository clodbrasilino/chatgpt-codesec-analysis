#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return 0;
        }
        ++str;
    }

    return 1;
}

int main(void)
{
    size_t length = 0;
    size_t capacity = 128;
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
            if (ferror(stdin) || length == 0) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        size_t index = 0;

        while (buffer[index] != '\0') {
            char character = buffer[index++];

            if (character == '\n' || character == '\r') {
                input[length] = '\0';
                puts(is_binary_string(input) ? "Binary string"
                                             : "Not a binary string");
                free(input);
                return EXIT_SUCCESS;
            }

            if (length > SIZE_MAX - 2) {
                free(input);
                return EXIT_FAILURE;
            }

            if (length + 1 >= capacity) {
                size_t required = length + 2;
                size_t new_capacity;
                char *temporary;

                if (capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                } else {
                    new_capacity = capacity * 2;
                    if (new_capacity < required) {
                        new_capacity = required;
                    }
                }

                temporary = realloc(input, new_capacity);
                if (temporary == NULL) {
                    free(input);
                    return EXIT_FAILURE;
                }

                input = temporary;
                capacity = new_capacity;
            }

            input[length++] = character;
        }
    }

    input[length] = '\0';
    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");

    free(input);
    return EXIT_SUCCESS;
}