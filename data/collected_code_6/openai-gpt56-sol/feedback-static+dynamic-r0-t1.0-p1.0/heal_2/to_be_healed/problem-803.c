#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

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

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
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