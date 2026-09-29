#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000000U

static int is_valid_number(const char *number)
{
    const unsigned char *p;

    if (number == NULL || *number == '\0') {
        return 0;
    }

    for (p = (const unsigned char *)number; *p != '\0'; ++p) {
        if (!isdigit(*p)) {
            return 0;
        }
    }

    return 1;
}

static char *next_palindrome(const char *number)
{
    size_t length;
    size_t i;
    size_t left;
    size_t right;
    char *palindrome;

    if (!is_valid_number(number)) {
        return NULL;
    }

    while (number[0] == '0' && number[1] != '\0') {
        ++number;
    }

    length = strlen(number);
    if (length > SIZE_MAX - 2U) {
        return NULL;
    }

    palindrome = malloc(length + 2U);
    if (palindrome == NULL) {
        return NULL;
    }

    memcpy(palindrome, number, length);
    palindrome[length] = '\0';

    for (i = 0; i < length / 2U; ++i) {
        palindrome[length - 1U - i] = palindrome[i];
    }

    if (strcmp(palindrome, number) > 0) {
        return palindrome;
    }

    left = (length - 1U) / 2U;
    right = length / 2U;

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
    if (length > 1U) {
        memset(palindrome + 1U, '0', length - 1U);
    }
    palindrome[length] = '1';
    palindrome[length + 1U] = '\0';

    return palindrome;
}

int main(void)
{
    char *input;
    char *result;
    size_t capacity = MAX_DIGITS + 2U;
    size_t length;
    int ch;

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

    length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Input is too long or malformed.\n");
            free(input);
            return EXIT_FAILURE;
        }

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    }

    if (length == 0U || length > MAX_DIGITS || !is_valid_number(input)) {
        fprintf(stderr, "Input must contain only decimal digits.\n");
        free(input);
        return EXIT_FAILURE;
    }

    result = next_palindrome(input);
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