#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_numeric_values(const char *text)
{
    size_t count = 0;
    int in_number = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isdigit((unsigned char)*text) != 0) {
            if (!in_number) {
                if (count == SIZE_MAX) {
                    return SIZE_MAX;
                }
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }

        ++text;
    }

    return count;
}

int main(void)
{
    char *input;
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    int status = EXIT_FAILURE;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_numeric_values(input)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}