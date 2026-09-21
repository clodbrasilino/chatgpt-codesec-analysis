#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_number(const char *number)
{
    const unsigned char *p = (const unsigned char *)number;

    if (p == NULL || *p == '\0') {
        return 0;
    }

    while (*p != '\0') {
        if (!isdigit(*p)) {
            return 0;
        }
        ++p;
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

static char *read_line(FILE *stream)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
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

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return NULL;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    char *result;

    input = read_line(stdin);
    if (input == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_number(input)) {
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