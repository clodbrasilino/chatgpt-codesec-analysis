#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const unsigned char *data,
                                 size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] < 2) {
            ++frequencies[data[i]];
        }
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    unsigned char *input = NULL;
    unsigned char result;
    size_t length = 0;
    size_t capacity = 128;
    int ch = EOF;
    int status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity >= MAX_INPUT_LENGTH) {
                break;
            }

            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too long.\n", stderr);
                goto cleanup;
            }

            new_capacity = capacity * 2;
            if (new_capacity > MAX_INPUT_LENGTH) {
                new_capacity = MAX_INPUT_LENGTH;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (length == MAX_INPUT_LENGTH && ch != '\n' && ch != EOF) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            goto cleanup;
        }
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        goto cleanup;
    }

    if (first_non_repeated_character(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            fputs("Failed to write output.\n", stderr);
            goto cleanup;
        }
    } else {
        if (puts("No non-repeated character found.") == EOF) {
            fputs("Failed to write output.\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}