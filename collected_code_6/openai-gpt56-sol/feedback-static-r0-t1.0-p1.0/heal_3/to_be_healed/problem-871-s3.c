#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U || capacity > (size_t)INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
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
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return false;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    size_t first_length = strnlen(first, MAX_INPUT_LENGTH + 1U);
    size_t second_length = strnlen(second, MAX_INPUT_LENGTH + 1U);

    if (first_length > MAX_INPUT_LENGTH ||
        second_length > MAX_INPUT_LENGTH ||
        first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    size_t buffer_size = first_length * 2U + 1U;
    char *doubled = malloc(buffer_size);

    if (doubled == NULL) {
        return false;
    }

    for (size_t i = 0U; i < first_length; ++i) {
        doubled[i] = first[i];
        doubled[first_length + i] = first[i];
    }

    doubled[2U * first_length] = '\0';

    bool result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char *first = malloc(MAX_INPUT_LENGTH + 1U);
    char *second = malloc(MAX_INPUT_LENGTH + 1U);

    if (first == NULL || second == NULL) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    if (!read_line(first, MAX_INPUT_LENGTH + 1U) ||
        !read_line(second, MAX_INPUT_LENGTH + 1U)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    puts(are_rotations(first, second) ? "Yes" : "No");

    free(first);
    free(second);
    return EXIT_SUCCESS;
}