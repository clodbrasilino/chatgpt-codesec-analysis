#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] < 2) {
            ++frequencies[data[i]];
        }
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

static int append_byte(unsigned char **data,
                       size_t *length,
                       size_t *capacity,
                       unsigned char value)
{
    unsigned char *temporary;
    size_t required;
    size_t new_capacity;

    if (data == NULL || length == NULL || capacity == NULL) {
        return 0;
    }

    if (*length == SIZE_MAX) {
        return 0;
    }

    required = *length + 1;

    if (required > *capacity) {
        new_capacity = *capacity == 0 ? 1024 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2;
        }

        temporary = realloc(*data, new_capacity);
        if (temporary == NULL) {
            return 0;
        }

        *data = temporary;
        *capacity = new_capacity;
    }

    (*data)[*length] = value;
    ++*length;
    return 1;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char result;
    int status = EXIT_SUCCESS;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (!append_byte(&input, &length, &capacity,
                         (unsigned char)character)) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (status == EXIT_SUCCESS && ferror(stdin)) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS) {
        if (find_first_non_repeated(input, length, &result)) {
            if (putchar((int)result) == EOF || putchar('\n') == EOF) {
                status = EXIT_FAILURE;
            }
        } else if (puts("No non-repeated character found") == EOF) {
            status = EXIT_FAILURE;
        }
    }

    free(input);
    return status;
}