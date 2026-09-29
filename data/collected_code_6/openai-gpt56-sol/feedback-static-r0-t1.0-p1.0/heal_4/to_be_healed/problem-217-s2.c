#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || repeated == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = *string++;

        if (seen[character]) {
            *repeated = character;
            return true;
        }

        seen[character] = true;
    }

    return false;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length > SIZE_MAX - 2) {
            goto cleanup;
        }

        if (capacity - length <= 1) {
            size_t required = length + 2;
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            unsigned char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = 1;
    }

    input[length] = '\0';

    unsigned char repeated;
    if (find_first_repeated_character(input, &repeated)) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            goto cleanup;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}