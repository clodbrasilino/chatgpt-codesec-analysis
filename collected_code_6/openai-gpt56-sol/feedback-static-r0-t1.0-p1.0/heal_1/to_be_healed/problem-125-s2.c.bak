#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int max_zero_one_difference(const char *string, size_t *start, size_t *end)
{
    int current = 0;
    int maximum = 0;
    size_t current_start = 0;

    *start = 0;
    *end = 0;

    for (size_t i = 0; string[i] != '\0'; ++i) {
        int value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        /* Possible weaknesses found:
         *  Invalid test for overflow 'current+value<value'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'current<0'. [invalidTestForOverflow]
         */
        if (current + value < value) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
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

    if (length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    size_t start;
    size_t end;
    int result = max_zero_one_difference(input, &start, &end);

    if (result < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    free(input);
    return EXIT_SUCCESS;
}