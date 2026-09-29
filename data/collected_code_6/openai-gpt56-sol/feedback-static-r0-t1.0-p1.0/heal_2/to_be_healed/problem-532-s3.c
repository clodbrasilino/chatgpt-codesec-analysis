#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static bool are_permutations(const char *first, const char *second)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (first == NULL || second == NULL) {
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        ++frequencies[(unsigned char)*first++];

        if (frequencies[(unsigned char)*second] == 0) {
            size_t i;
            const unsigned char *remaining = (const unsigned char *)second;

            for (i = 0; remaining[i] != '\0'; ++i) {
                ++frequencies[remaining[i]];
            }

            return false;
        }

        --frequencies[(unsigned char)*second++];
    }

    return *first == '\0' && *second == '\0';
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *first = read_line(stdin);
    char *second;
    int result;

    if (first == NULL) {
        return 1;
    }

    second = read_line(stdin);
    if (second == NULL) {
        free(first);
        return 1;
    }

    result = printf("%s\n",
                    are_permutations(first, second) ? "true" : "false");

    free(second);
    free(first);

    return result < 0 ? 1 : 0;
}