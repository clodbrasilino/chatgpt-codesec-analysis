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

    for (;;) {
        if (length == capacity - 1) {
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            capacity *= 2;
            resized = realloc(buffer, capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }
            buffer = resized;
        }

        buffer[length++] = (char)ch;

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

    while (source[index] != '\0' && target[index] != '\0') {
        if ((source[index] != '0' && source[index] != '1') ||
            (target[index] != '0' && target[index] != '1')) {
            return -1;
        }

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