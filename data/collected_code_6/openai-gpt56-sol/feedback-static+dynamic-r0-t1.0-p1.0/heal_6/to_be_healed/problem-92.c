#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_undulating(unsigned long long number)
{
    unsigned int first;
    unsigned int second;
    bool expect_first = true;
    unsigned long long value = number;

    if (number < 100ULL) {
        return false;
    }

    first = (unsigned int)(value % 10ULL);
    value /= 10ULL;
    second = (unsigned int)(value % 10ULL);

    if (first == second) {
        return false;
    }

    while (value != 0ULL) {
        unsigned int digit = (unsigned int)(value % 10ULL);
        unsigned int expected = expect_first ? first : second;

        if (digit != expected) {
            return false;
        }

        expect_first = !expect_first;
        value /= 10ULL;
    }

    return true;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(buffer);
                    return NULL;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stream) || length == 0U)) {
        free(buffer);
        return NULL;
    }

    if (length == SIZE_MAX) {
        free(buffer);
        return NULL;
    }

    if (capacity <= length) {
        char *new_buffer = realloc(buffer, length + 1U);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    unsigned long long number;

    input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_undulating(number) ? "Undulating" : "Not undulating");

    free(input);
    return EXIT_SUCCESS;
}