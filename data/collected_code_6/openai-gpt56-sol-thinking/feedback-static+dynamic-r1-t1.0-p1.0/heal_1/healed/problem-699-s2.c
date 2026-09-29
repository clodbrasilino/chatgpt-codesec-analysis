#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_token(FILE *stream, char **output)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    do {
        ch = fgetc(stream);
        if (ch == EOF) {
            return ferror(stream) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                free(buffer);
                return -1;
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
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

static int is_binary_string(const char *string)
{
    size_t index;

    if (string == NULL) {
        return 0;
    }

    for (index = 0; string[index] != '\0'; ++index) {
        if (string[index] != '0' && string[index] != '1') {
            return 0;
        }
    }

    return 1;
}

static int minimum_swaps(const char *source, const char *target, size_t *result)
{
    size_t index = 0;
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    if (!is_binary_string(source) || !is_binary_string(target)) {
        return -1;
    }

    while (source[index] != '\0' && target[index] != '\0') {
        if (source[index] == '0' && target[index] == '1') {
            ++zero_to_one;
        } else if (source[index] == '1' && target[index] == '0') {
            ++one_to_zero;
        }

        ++index;
    }

    if (source[index] != '\0' || target[index] != '\0') {
        return 1;
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
    size_t swaps = 0;
    int status;

    status = read_token(stdin, &source);
    if (status != 1) {
        fprintf(stderr, "Failed to read the first binary string.\n");
        return EXIT_FAILURE;
    }

    status = read_token(stdin, &target);
    if (status != 1) {
        fprintf(stderr, "Failed to read the second binary string.\n");
        free(source);
        return EXIT_FAILURE;
    }

    status = minimum_swaps(source, target, &swaps);

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