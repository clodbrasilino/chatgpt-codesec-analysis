#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 ||
        mismatches_01 > (size_t)INT_MAX) {
        return -1;
    }

    return (int)mismatches_01;
}

static char *read_word(void)
{
    size_t length = 0;
    size_t capacity = 32;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    do {
        ch = getchar();
    } while (ch != EOF &&
             (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'));

    if (ch == EOF) {
        free(buffer);
        return NULL;
    }

    do {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF &&
             ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n');

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *first = read_word();
    char *second;
    size_t first_length;
    size_t second_length;
    int result;

    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_word();
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        result = -1;
    } else {
        result = minimum_swaps(first, second, first_length);
    }

    printf("%d\n", result);

    free(second);
    free(first);
    return EXIT_SUCCESS;
}