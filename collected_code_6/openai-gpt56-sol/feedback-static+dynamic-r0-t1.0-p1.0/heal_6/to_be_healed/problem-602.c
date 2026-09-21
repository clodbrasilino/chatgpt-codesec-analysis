#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    while (*str != '\0') {
        unsigned char current = (unsigned char)*str++;

        if (seen[current] != 0U) {
            *result = current;
            return 1;
        }

        seen[current] = 1U;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        size_t required;
        char *new_input;

        if (length > SIZE_MAX - 2U) {
            free(input);
            return EXIT_FAILURE;
        }

        required = length + 2U;

        if (capacity < required) {
            size_t new_capacity = (capacity == 0U) ? 128U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    {
        unsigned char repeated;

        if (find_first_repeated_character(input, &repeated)) {
            if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
                free(input);
                return EXIT_FAILURE;
            }
        } else if (puts("No repeated character") == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);
    return EXIT_SUCCESS;
}