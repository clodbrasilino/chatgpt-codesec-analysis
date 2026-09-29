#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        ++length;
    }

    return length;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX / 2)) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            char *temp = realloc(input, new_capacity);
            if (temp == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temp;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);

    free(input);
    return EXIT_SUCCESS;
}