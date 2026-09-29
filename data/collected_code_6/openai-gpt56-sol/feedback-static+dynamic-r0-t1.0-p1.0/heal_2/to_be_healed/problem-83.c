#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + (unsigned char)*string) % 256U;
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity <= capacity) {
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

        input[length++] = (char)character;
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

    unsigned char result = add_characters(input);
    free(input);

    if (printf("%c\n", (int)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}