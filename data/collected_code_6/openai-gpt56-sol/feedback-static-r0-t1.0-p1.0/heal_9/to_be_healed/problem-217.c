#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str++;

        if (seen[ch] != 0) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated = 0;
    int status = EXIT_SUCCESS;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                status = EXIT_FAILURE;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            status = EXIT_FAILURE;
            break;
        }

        size_t required = length + 2;

        if (required > capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                status = EXIT_FAILURE;
                break;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (status == EXIT_SUCCESS && length != 0) {
        input[length] = '\0';

        if (find_first_repeated_character(input, &repeated) != 0) {
            if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
                status = EXIT_FAILURE;
            }
        } else if (puts("No repeated character") == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(input);
    return status;
}