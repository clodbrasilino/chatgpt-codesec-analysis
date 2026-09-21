#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_difference_of_two_squares(int64_t number)
{
    int64_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

static int read_line(char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = malloc(capacity);
    if (*buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(*buffer);
                *buffer = NULL;
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                free(*buffer);
                *buffer = NULL;
                return 0;
            }

            *buffer = new_buffer;
            capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(*buffer);
        *buffer = NULL;
        return 0;
    }

    (*buffer)[length] = '\0';
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    intmax_t value = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares((int64_t)value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}