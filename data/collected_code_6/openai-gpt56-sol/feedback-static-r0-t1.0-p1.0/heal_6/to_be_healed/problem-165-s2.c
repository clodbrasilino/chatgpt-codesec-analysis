#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (tolower(ch) == 'a' + (int)i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = length + 1;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_matching_positions(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}