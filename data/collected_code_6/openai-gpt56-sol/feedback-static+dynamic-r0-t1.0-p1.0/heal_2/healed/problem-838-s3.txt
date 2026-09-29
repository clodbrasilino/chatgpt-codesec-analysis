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

    if (mismatches_01 != mismatches_10 || mismatches_01 > (size_t)INT_MAX) {
        return -1;
    }

    return (int)mismatches_01;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return NULL;
                }
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity || new_capacity < length + 2) {
                free(buffer);
                return NULL;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(buffer, length + 1);

        if (resized == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = resized;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *first = read_line(stdin);
    char *second;
    size_t first_length;
    size_t second_length;
    int result;

    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_line(stdin);
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        puts("-1");
        free(first);
        free(second);
        return EXIT_SUCCESS;
    }

    result = minimum_swaps(first, second, first_length);
    printf("%d\n", result);

    free(first);
    free(second);
    return EXIT_SUCCESS;
}