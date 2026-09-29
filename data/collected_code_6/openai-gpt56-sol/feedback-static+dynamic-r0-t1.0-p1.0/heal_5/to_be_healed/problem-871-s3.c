#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_CAPACITY 1024U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    buffer[0] = '\0';
    return false;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t index = 0U;

        while (index < first_length &&
               first[index] == second[(index + offset) % first_length]) {
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

    if (!read_line(first, sizeof first) ||
        !read_line(second, sizeof second)) {
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");
    return EXIT_SUCCESS;
}