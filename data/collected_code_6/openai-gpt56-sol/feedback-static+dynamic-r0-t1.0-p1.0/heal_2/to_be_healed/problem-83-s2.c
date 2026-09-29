#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned char add_characters(const char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + (unsigned char)*string) % (UCHAR_MAX + 1U);
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
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("getchar");
        free(input);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';
    printf("%c\n", add_characters(input));

    free(input);
    return 0;
}