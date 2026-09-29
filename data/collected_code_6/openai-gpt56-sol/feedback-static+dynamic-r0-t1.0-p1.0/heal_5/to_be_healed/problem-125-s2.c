#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static intmax_t max_zero_one_difference(const char *string,
                                        size_t *start,
                                        size_t *end)
{
    intmax_t current = 0;
    intmax_t maximum = 0;
    size_t current_start = 0;

    *start = 0;
    *end = 0;

    for (size_t i = 0; string[i] != '\0'; ++i) {
        intmax_t value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
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

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 64;
    char *input = malloc(capacity);

    if (input == NULL) {
        return 0;
    }

    *length = 0;

    while (fgets(input + *length,
                 (int)(capacity - *length),
                 stdin) != NULL) {
        size_t i = *length;

        while (input[i] != '\0' && input[i] != '\n') {
            ++i;
        }

        if (input[i] == '\n') {
            input[i] = '\0';
            *length = i;
            *buffer = input;
            return 1;
        }

        *length = i;

        if (feof(stdin)) {
            *buffer = input;
            return 1;
        }

        if (capacity > SIZE_MAX / 2) {
            free(input);
            return 0;
        }

        size_t new_capacity = capacity * 2;

        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        if (new_capacity > (size_t)INT_MAX) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             */
            new_capacity = (size_t)INT_MAX;
        }

        if (new_capacity <= capacity) {
            free(input);
            return 0;
        }

        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return 0;
        }

        input = new_input;
        capacity = new_capacity;
    }

    if (ferror(stdin) || *length == 0) {
        free(input);
        return 0;
    }

    input[*length] = '\0';
    *buffer = input;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;

    if (!read_line(&input, &length) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t start;
    size_t end;
    intmax_t result = max_zero_one_difference(input, &start, &end);

    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%jd\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}