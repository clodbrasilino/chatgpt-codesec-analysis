#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (seen[data[i]] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[data[i]] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity > SIZE_MAX / 2U) {
                if (capacity == SIZE_MAX) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            unsigned char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (find_first_repeated_character(input, length, &repeated)) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            free(input);
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}