#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_number(const char *number)
{
    size_t i;

    if (number == NULL || number[0] == '\0') {
        return 0;
    }

    for (i = 0; number[i] != '\0'; ++i) {
        if (!isdigit((unsigned char)number[i])) {
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
    int greater = 0;
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

    memcpy(palindrome, number, length + 1U);

    for (i = 0; i < length / 2U; ++i) {
        palindrome[length - 1U - i] = palindrome[i];
    }

    if (strcmp(palindrome, number) > 0) {
        return palindrome;
    }

    left = (length - 1U) / 2U;
    right = length / 2U;

    for (;;) {
        if (palindrome[left] < '9') {
            ++palindrome[left];
            palindrome[right] = palindrome[left];
            greater = 1;
            break;
        }

        palindrome[left] = '0';
        palindrome[right] = '0';

        if (left == 0U) {
            break;
        }

        --left;
        ++right;
    }

    if (greater) {
        return palindrome;
    }

    palindrome[0] = '1';
    for (i = 1; i < length; ++i) {
        palindrome[i] = '0';
    }
    palindrome[length] = '1';
    palindrome[length + 1U] = '\0';

    return palindrome;
}

int main(void)
{
    char input[1000002];
    char extra;
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        if (scanf("%c", &extra) == 1) {
            fprintf(stderr, "Input is too long or malformed.\n");
            return EXIT_FAILURE;
        }
    } else {
        input[strcspn(input, "\n")] = '\0';
    }

    input[strcspn(input, "\r")] = '\0';

    if (!is_valid_number(input)) {
        fprintf(stderr, "Input must contain only decimal digits.\n");
        return EXIT_FAILURE;
    }

    result = next_palindrome(input);
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