#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

enum { INITIAL_CAPACITY = 128 };

static bool has_two_alternating_characters(const char *string, size_t length)
{
    if (string == NULL || length < 2U || string[0] == string[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (string[i] != string[i % 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(input + length, (int)(capacity - length), stdin) != NULL) {
        size_t i = length;

        while (input[i] != '\0' && input[i] != '\n') {
            ++i;
        }

        if (input[i] == '\n') {
            length = i;
            input[length] = '\0';
            break;
        }

        length = i;

        if (feof(stdin)) {
            break;
        }

        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }

        if (capacity > SIZE_MAX / 2U) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t new_capacity = capacity * 2U;

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
            return EXIT_FAILURE;
        }

        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}