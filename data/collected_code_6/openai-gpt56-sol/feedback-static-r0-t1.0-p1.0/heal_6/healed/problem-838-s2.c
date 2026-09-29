#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LENGTH ((size_t)100000)

static int is_whitespace(int character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static int read_binary_string(char **string, size_t *length)
{
    char *buffer;
    size_t capacity = 128;
    size_t used = 0;
    int character;

    if (string == NULL || length == NULL) {
        return 0;
    }

    *string = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    do {
        character = fgetc(stdin);
        if (character == EOF) {
            free(buffer);
            return 0;
        }
    } while (is_whitespace(character));

    while (character != EOF && !is_whitespace(character)) {
        if (character != '0' && character != '1') {
            free(buffer);
            return 0;
        }

        if (used == MAX_LENGTH) {
            free(buffer);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (MAX_LENGTH + 1) / 2) {
                new_capacity = MAX_LENGTH + 1;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity || new_capacity > MAX_LENGTH + 1) {
                free(buffer);
                return 0;
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
        character = fgetc(stdin);
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
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return 0;
        }

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
    size_t first_length = 0;
    size_t second_length = 0;
    size_t swaps;

    if (!read_binary_string(&first, &first_length) ||
        !read_binary_string(&second, &second_length)) {
        free(first);
        free(second);
        fputs("Invalid input\n", stderr);
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