#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define INPUT_CAPACITY 1024U

static bool discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin) != 0;
}

static bool read_line(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL ||
        capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    buffer[0] = '\0';
    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t used = strlen(buffer);

    if (used > 0U && buffer[used - 1U] == '\n') {
        buffer[--used] = '\0';

        if (used > 0U && buffer[used - 1U] == '\r') {
            buffer[--used] = '\0';
        }

        *length = used;
        return true;
    }

    if (feof(stdin)) {
        if (used > 0U && buffer[used - 1U] == '\r') {
            buffer[--used] = '\0';
        }

        *length = used;
        return true;
    }

    buffer[0] = '\0';
    (void)discard_line();
    return false;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t index = 0U;

        while (index < first_length) {
            size_t second_index = index + offset;

            if (second_index >= first_length) {
                second_index -= first_length;
            }

            if (first[index] != second[second_index]) {
                break;
            }

            ++index;
        }

        if (index == first_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[INPUT_CAPACITY];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[INPUT_CAPACITY];
    size_t first_length;
    size_t second_length;

    if (!read_line(first, sizeof first, &first_length) ||
        !read_line(second, sizeof second, &second_length)) {
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, first_length, second, second_length)
             ? "Yes"
             : "No");

    return EXIT_SUCCESS;
}