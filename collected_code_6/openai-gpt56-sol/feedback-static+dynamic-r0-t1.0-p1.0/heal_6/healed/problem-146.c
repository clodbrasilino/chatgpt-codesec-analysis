#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int print_ascii_values(const unsigned char *string, size_t length)
{
    if (string == NULL && length != 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%u\n", (unsigned int)string[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *string = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int result = EXIT_FAILURE;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                perror("fgetc");
                goto cleanup;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length >= capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity > SIZE_MAX / 2) {
                goto cleanup;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length] = (unsigned char)character;
        ++length;
    }

    if (print_ascii_values(string, length) != 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(string);
    return result;
}