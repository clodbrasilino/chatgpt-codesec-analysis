#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000000U

static int is_valid_number(const char *number, size_t length)
{
    size_t i;

    if (number == NULL || length == 0U) {
        return 0;
    }

    for (i = 0U; i < length; ++i) {
        if (!isdigit((unsigned char)number[i])) {
            return 0;
        }
    }

    return 1;
}

static char *next_palindrome(const char *number, size_t length)
{
    char *palindrome;
    size_t offset = 0U;
    size_t normalized_length;
    size_t allocation_size;
    size_t i;
    size_t left;
    size_t right;

    if (number == NULL || length == 0U) {
        return NULL;
    }

    while (offset + 1U < length && number[offset] == '0') {
        ++offset;
    }

    number += offset;
    normalized_length = length - offset;

    if (normalized_length > SIZE_MAX - 2U) {
        return NULL;
    }

    allocation_size = normalized_length + 2U;
    palindrome = malloc(allocation_size);
    if (palindrome == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(palindrome, number, normalized_length);
    palindrome[normalized_length] = '\0';

    for (i = 0U; i < normalized_length / 2U; ++i) {
        palindrome[normalized_length - 1U - i] = palindrome[i];
    }

    if (memcmp(palindrome, number, normalized_length) > 0) {
        return palindrome;
    }

    left = (normalized_length - 1U) / 2U;
    right = normalized_length / 2U;

    for (;;) {
        if (palindrome[left] != '9') {
            ++palindrome[left];
            palindrome[right] = palindrome[left];
            return palindrome;
        }

        palindrome[left] = '0';
        palindrome[right] = '0';

        if (left == 0U) {
            break;
        }

        --left;
        ++right;
    }

    palindrome[0] = '1';

    if (normalized_length > 1U) {
        memset(palindrome + 1U, '0', normalized_length - 1U);
    }

    palindrome[normalized_length] = '1';
    palindrome[normalized_length + 1U] = '\0';

    return palindrome;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

static int read_number(char *buffer, size_t capacity, size_t *length)
{
    char *newline;
    size_t used;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    int next;

    if (buffer == NULL || length == NULL || capacity < 2U ||
        capacity > (size_t)INT32_MAX) {
        return -1;
    }

    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        used = (size_t)(newline - buffer);

        if (used > 0U && buffer[used - 1U] == '\r') {
            --used;
        }

        buffer[used] = '\0';
        *length = used;
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    used = strlen(buffer);

    if (used == capacity - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            if (discard_line() < 0) {
                return -1;
            }
            return 1;
        }

        if (next == EOF && ferror(stdin)) {
            return -1;
        }
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
        buffer[used] = '\0';
    }

    *length = used;
    return 0;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_DIGITS + 2U;
    char *input;
    char *result;
    size_t length;
    int status;

    if (capacity > (size_t)INT32_MAX) {
        fputs("Input capacity is unsupported.\n", stderr);
        return EXIT_FAILURE;
    }

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Unable to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_number(input, capacity, &length);
    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        fputs("Input is too long or malformed.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0U || length > (size_t)MAX_DIGITS ||
        !is_valid_number(input, length)) {
        fputs("Input must contain only decimal digits.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    result = next_palindrome(input, length);
    free(input);

    if (result == NULL) {
        fputs("Unable to compute the next palindrome.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}