#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LENGTH 100000U

static int read_binary_string(char **string, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);
    int character;

    if (string == NULL || length == NULL || buffer == NULL) {
        free(buffer);
        return 0;
    }

    do {
        character = getchar();
    } while (character != EOF &&
             (character == ' ' || character == '\t' ||
              character == '\n' || character == '\r' ||
              character == '\f' || character == '\v'));

    if (character == EOF) {
        free(buffer);
        return 0;
    }

    while (character != EOF &&
           character != ' ' && character != '\t' &&
           character != '\n' && character != '\r' &&
           character != '\f' && character != '\v') {
        char *resized;
        size_t new_capacity;

        if (character != '0' && character != '1') {
            free(buffer);
            return 0;
        }

        if (used >= MAX_LENGTH) {
            free(buffer);
            return 0;
        }

        if (used + 1 >= capacity) {
            new_capacity = capacity * 2;
            if (new_capacity > MAX_LENGTH + 1) {
                new_capacity = MAX_LENGTH + 1;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
        character = getchar();
    }

    if (used == 0) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *string = buffer;
    *length = used;
    return 1;
}

static int minimum_swaps(const char *first, size_t first_length,
                         const char *second, size_t second_length,
                         size_t *result)
{
    size_t zero_one = 0;
    size_t one_zero = 0;

    if (first == NULL || second == NULL || result == NULL ||
        first_length != second_length) {
        return 0;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (first[i] == '0' && second[i] == '1') {
            ++zero_one;
        } else if (first[i] == '1' && second[i] == '0') {
            ++one_zero;
        }
    }

    if ((zero_one & 1U) != (one_zero & 1U)) {
        return 0;
    }

    *result = zero_one / 2U + one_zero / 2U +
              2U * (zero_one & 1U);
    return 1;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length;
    size_t second_length;
    size_t swaps;

    if (!read_binary_string(&first, &first_length) ||
        !read_binary_string(&second, &second_length)) {
        free(first);
        free(second);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(first, first_length, second, second_length, &swaps)) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    free(first);
    free(second);
    return EXIT_SUCCESS;
}