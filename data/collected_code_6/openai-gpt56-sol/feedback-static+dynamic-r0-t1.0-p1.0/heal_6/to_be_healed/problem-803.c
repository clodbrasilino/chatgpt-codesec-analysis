#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return NULL;
                }

                new_capacity = capacity * 2;
            }

            char *temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return NULL;
        }
    } else if (length == capacity) {
        char *temporary = realloc(buffer, length + 1);
        if (temporary == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = temporary;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    bool valid = *start != '\0' && *start != '-';
    uintmax_t number = 0;
    char *end = start;

    if (valid) {
        errno = 0;
        number = strtoumax(start, &end, 10);
        valid = errno != ERANGE && end != start;
    }

    if (valid) {
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        valid = *end == '\0';
    }

    puts(valid && is_perfect_square(number) ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}