#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_size(size_t *total, size_t amount)
{
    if (amount > SIZE_MAX - *total) {
        errno = EOVERFLOW;
        return -1;
    }

    *total += amount;
    return 0;
}

static size_t escaped_character_length(unsigned char character)
{
    if (character == '"' || character == '\\' ||
        character == '\n' || character == '\r' ||
        character == '\t' || character == '\b' ||
        character == '\f') {
        return 2;
    }

    if (character < 0x20 || character == 0x7f) {
        return 4;
    }

    return 1;
}

static char *append_escaped_string(char *destination, const char *source)
{
    static const char hexadecimal[] = "0123456789abcdef";

    while (*source != '\0') {
        const unsigned char character = (unsigned char)*source++;

        switch (character) {
        case '"':
            *destination++ = '\\';
            *destination++ = '"';
            break;

        case '\\':
            *destination++ = '\\';
            *destination++ = '\\';
            break;

        case '\n':
            *destination++ = '\\';
            *destination++ = 'n';
            break;

        case '\r':
            *destination++ = '\\';
            *destination++ = 'r';
            break;

        case '\t':
            *destination++ = '\\';
            *destination++ = 't';
            break;

        case '\b':
            *destination++ = '\\';
            *destination++ = 'b';
            break;

        case '\f':
            *destination++ = '\\';
            *destination++ = 'f';
            break;

        default:
            if (character < 0x20 || character == 0x7f) {
                *destination++ = '\\';
                *destination++ = 'x';
                *destination++ = hexadecimal[character >> 4];
                *destination++ = hexadecimal[character & 0x0f];
            } else {
                *destination++ = (char)character;
            }
            break;
        }
    }

    return destination;
}

char *string_list_to_tuple(const char *const list[], size_t count)
{
    size_t required_size = 3;
    char *tuple;
    char *position;

    if (count > 0 && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const unsigned char *current;

        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i > 0 && add_size(&required_size, 2) != 0) {
            return NULL;
        }

        if (add_size(&required_size, 2) != 0) {
            return NULL;
        }

        current = (const unsigned char *)list[i];

        while (*current != '\0') {
            if (add_size(&required_size,
                         escaped_character_length(*current)) != 0) {
                return NULL;
            }

            ++current;
        }
    }

    if (count == 1 && add_size(&required_size, 1) != 0) {
        return NULL;
    }

    tuple = malloc(required_size);
    if (tuple == NULL) {
        return NULL;
    }

    position = tuple;
    *position++ = '(';

    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            *position++ = ',';
            *position++ = ' ';
        }

        *position++ = '"';
        position = append_escaped_string(position, list[i]);
        *position++ = '"';
    }

    if (count == 1) {
        *position++ = ',';
    }

    *position++ = ')';
    *position = '\0';

    return tuple;
}

int main(int argc, char *const argv[])
{
    const size_t count = argc > 1 ? (size_t)(argc - 1) : 0;
    const char **arguments = NULL;
    char *tuple;

    if (count > 0) {
        if (count > SIZE_MAX / sizeof(*arguments)) {
            errno = EOVERFLOW;
            perror("string_list_to_tuple");
            return EXIT_FAILURE;
        }

        arguments = malloc(count * sizeof(*arguments));
        if (arguments == NULL) {
            perror("string_list_to_tuple");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < count; ++i) {
            arguments[i] = argv[i + 1];
        }
    }

    tuple = string_list_to_tuple(arguments, count);
    free(arguments);

    if (tuple == NULL) {
        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    if (fputs(tuple, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        const int saved_errno = errno;

        free(tuple);
        errno = saved_errno;
        perror("output");
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}