#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(intmax_t number)
{
    intmax_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

static bool read_line(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL) {
        return false;
    }

    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity == 0 ? 128 : *capacity * 2;

            if (new_capacity <= *capacity) {
                free(*buffer);
                *buffer = NULL;
                *capacity = 0;
                return false;
            }

            char *resized = realloc(*buffer, new_capacity);
            if (resized == NULL) {
                free(*buffer);
                *buffer = NULL;
                *capacity = 0;
                return false;
            }

            *buffer = resized;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(*buffer);
        *buffer = NULL;
        *capacity = 0;
        return false;
    }

    if (*buffer == NULL) {
        *capacity = 1;
        *buffer = malloc(*capacity);
        if (*buffer == NULL) {
            *capacity = 0;
            return false;
        }
    }

    (*buffer)[length] = '\0';
    return true;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;

    if (!read_line(&input, &capacity)) {
        return EXIT_FAILURE;
    }

    char *end;
    errno = 0;
    intmax_t number = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input) {
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

    free(input);

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}