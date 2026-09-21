#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH ((size_t)1048576)

static int read_token(FILE *stream, char **output, size_t *output_length)
{
    const size_t maximum_capacity = MAX_TOKEN_LENGTH + 1;
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            return ferror(stream) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    if (capacity > maximum_capacity) {
        capacity = maximum_capacity;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length >= MAX_TOKEN_LENGTH) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= maximum_capacity) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            if (new_capacity > maximum_capacity) {
                new_capacity = maximum_capacity;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;
    return 1;
}

static int minimum_swaps(const char *source, size_t source_length,
                         const char *target, size_t target_length,
                         size_t *result)
{
    size_t index;
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    for (index = 0; index < source_length; ++index) {
        if (source[index] != '0' && source[index] != '1') {
            return -1;
        }
    }

    for (index = 0; index < target_length; ++index) {
        if (target[index] != '0' && target[index] != '1') {
            return -1;
        }
    }

    if (source_length != target_length) {
        return 1;
    }

    for (index = 0; index < source_length; ++index) {
        if (source[index] == '0' && target[index] == '1') {
            ++zero_to_one;
        } else if (source[index] == '1' && target[index] == '0') {
            ++one_to_zero;
        }
    }

    if (zero_to_one != one_to_zero) {
        return 1;
    }

    *result = zero_to_one;
    return 0;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;

    status = read_token(stdin, &source, &source_length);
    if (status != 1) {
        fprintf(stderr, "Failed to read the first binary string.\n");
        return EXIT_FAILURE;
    }

    status = read_token(stdin, &target, &target_length);
    if (status != 1) {
        fprintf(stderr, "Failed to read the second binary string.\n");
        free(source);
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, source_length, target, target_length,
                           &swaps);

    free(source);
    free(target);

    if (status < 0) {
        fprintf(stderr, "Invalid binary string.\n");
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%zu\n", swaps);
    return EXIT_SUCCESS;
}