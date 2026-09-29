#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

static bool is_perfect_square(uintmax_t number)
{
    uintmax_t left = 0;
    uintmax_t right = number;

    while (left <= right) {
        uintmax_t middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            uintmax_t square = middle * middle;

            if (square == number) {
                return true;
            }

            left = middle + 1;
        }
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
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

    if (ferror(stdin) || (character == EOF && length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    if (capacity < length + 1) {
        char *new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = new_input;
    }

    input[length] = '\0';

    char *start = input;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t number = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX " is%s a perfect square.\n",
           number, is_perfect_square(number) ? "" : " not");

    free(input);
    return EXIT_SUCCESS;
}