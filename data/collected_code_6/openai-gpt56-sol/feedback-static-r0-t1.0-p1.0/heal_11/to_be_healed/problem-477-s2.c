#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int string_to_lower(char *string)
{
    unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (unsigned char *)string;

    while (*current != '\0') {
        *current = (unsigned char)tolower(*current);
        ++current;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int status = EXIT_FAILURE;

    for (;;) {
        int character;

        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (capacity <= length) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                perror("fgetc");
                goto cleanup;
            }
            break;
        }

        input[length++] = (char)(unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (length == 0) {
        status = EXIT_SUCCESS;
        goto cleanup;
    }

    input[length] = '\0';

    if (string_to_lower(input) != 0) {
        goto cleanup;
    }

    if (fputs(input, stdout) == EOF) {
        perror("fputs");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}