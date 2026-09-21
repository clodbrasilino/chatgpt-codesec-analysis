#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (first == NULL || second == NULL) {
        return -1;
    }

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

static char *read_word(size_t *word_length)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (word_length == NULL) {
        return NULL;
    }

    *word_length = 0;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    do {
        ch = fgetc(stdin);
    } while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');

    if (ch == EOF) {
        free(buffer);
        return NULL;
    }

    while (ch != EOF &&
           ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') {
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
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    *word_length = length;
    return buffer;
}

int main(void)
{
    char *first;
    char *second;
    size_t first_length;
    size_t second_length;
    int result;

    first = read_word(&first_length);
    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_word(&second_length);
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    if (first_length != second_length) {
        result = -1;
    } else {
        result = minimum_swaps(first, second, first_length);
    }

    if (printf("%d\n", result) < 0) {
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    free(second);
    free(first);
    return EXIT_SUCCESS;
}