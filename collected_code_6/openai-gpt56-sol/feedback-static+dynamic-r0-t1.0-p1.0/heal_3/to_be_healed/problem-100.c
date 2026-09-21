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
    size_t i;
    size_t left;
    size_t right;

    while (offset + 1U < length && number[offset] == '0') {
        ++offset;
    }

    number += offset;
    length -= offset;

    if (length > SIZE_MAX - 2U) {
        return NULL;
    }

    palindrome = malloc(length + 2U);
    if (palindrome == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(palindrome, number, length);
    palindrome[length] = '\0';

    for (i = 0U; i < length / 2U; ++i) {
        palindrome[length - 1U - i] = palindrome[i];
    }

    if (memcmp(palindrome, number, length) > 0) {
        return palindrome;
    }

    left = (length - 1U) / 2U;
    right = length / 2U;

    for (;;) {
        if (palindrome[left] < '9') {
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
    if (length > 1U) {
        memset(palindrome + 1U, '0', length - 1U);
    }
    palindrome[length] = '1';
    palindrome[length + 1U] = '\0';

    return palindrome;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_DIGITS + 2U;
    char *input;
    char *result;
    size_t length;

    if (capacity > (size_t)INT32_MAX) {
        fprintf(stderr, "Input capacity is unsupported.\n");
        return EXIT_FAILURE;
    }

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Unable to allocate input buffer.\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    length = strnlen(input, capacity);
    if (length == capacity) {
        fprintf(stderr, "Input is malformed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fprintf(stderr, "Input is too long or malformed.\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    }

    if (length == 0U || length > (size_t)MAX_DIGITS ||
        !is_valid_number(input, length)) {
        fprintf(stderr, "Input must contain only decimal digits.\n");
        free(input);
        return EXIT_FAILURE;
    }

    result = next_palindrome(input, length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Unable to compute the next palindrome.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}