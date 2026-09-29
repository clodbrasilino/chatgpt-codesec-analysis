#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

static uintmax_t last_digit(intmax_t number)
{
    return number < 0
        ? (uintmax_t)(-(number + 1)) % UINTMAX_C(10) + UINTMAX_C(1)
        : (uintmax_t)number % UINTMAX_C(10);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    char *end;
    intmax_t number;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    number = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%ju\n", last_digit(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}