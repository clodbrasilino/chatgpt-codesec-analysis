#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_size(size_t *total, size_t amount)
{
    if (total == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (amount > SIZE_MAX - *total) {
        errno = EOVERFLOW;
        return -1;
    }

    *total += amount;
    return 0;
}

static size_t escaped_character_length(unsigned char character)
{
    switch (character) {
        case '"':
        case '\\':
        case '\n':
        case '\r':
        case '\t':
        case '\b':
        case '\f':
            return 2;

        default:
            return character < 0x20 || character == 0x7f ? 4 : 1;
    }
}

static char hexadecimal_digit(unsigned char value)
{
    return value < 10
        ? (char)('0' + value)
        : (char)('a' + (value - 10));
}

static int append_character(
    char **destination,
    size_t *remaining,
    char character)
{
    if (destination == NULL || *destination == NULL || remaining == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*remaining == 0) {
        errno = EOVERFLOW;
        return -1;
    }

    **destination = character;
    ++*destination;
    --*remaining;
    return 0;
}

static int append_escaped_string(
    char **destination,
    size_t *remaining,
    const char *source)
{
    if (destination == NULL || remaining == NULL || source == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;
        size_t length = escaped_character_length(character);

        if (*remaining < length) {
            errno = EOVERFLOW;
            return -1;
        }

        switch (character) {
            case '"':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, '"') != 0) {
                    return -1;
                }
                break;

            case '\\':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, '\\') != 0) {
                    return -1;
                }
                break;

            case '\n':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, 'n') != 0) {
                    return -1;
                }
                break;

            case '\r':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, 'r') != 0) {
                    return -1;
                }
                break;

            case '\t':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, 't') != 0) {
                    return -1;
                }
                break;

            case '\b':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, 'b') != 0) {
                    return -1;
                }
                break;

            case '\f':
                if (append_character(destination, remaining, '\\') != 0 ||
                    append_character(destination, remaining, 'f') != 0) {
                    return -1;
                }
                break;

            default:
                if (character < 0x20 || character == 0x7f) {
                    if (append_character(destination, remaining, '\\') != 0 ||
                        append_character(destination, remaining, 'x') != 0 ||
                        append_character(
                            destination,
                            remaining,
                            hexadecimal_digit(
                                (unsigned char)(character >> 4))) != 0 ||
                        append_character(
                            destination,
                            remaining,
                            hexadecimal_digit(
                                (unsigned char)(character & 0x0f))) != 0) {
                        return -1;
                    }
                } else if (append_character(
                               destination,
                               remaining,
                               (char)character) != 0) {
                    return -1;
                }
                break;
        }
    }

    return 0;
}

char *string_list_to_tuple(const char *const *list, size_t count)
{
    size_t required_size = 3;
    char *tuple;
    char *position;
    size_t remaining;

    if (count != 0 && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const unsigned char *current;

        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i != 0 && add_size(&required_size, 2) != 0) {
            return NULL;
        }

        if (add_size(&required_size, 2) != 0) {
            return NULL;
        }

        current = (const unsigned char *)list[i];

        while (*current != '\0') {
            if (add_size(
                    &required_size,
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
        errno = ENOMEM;
        return NULL;
    }

    position = tuple;
    remaining = required_size - 1;

    if (append_character(&position, &remaining, '(') != 0) {
        goto failure;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i != 0) {
            if (append_character(&position, &remaining, ',') != 0 ||
                append_character(&position, &remaining, ' ') != 0) {
                goto failure;
            }
        }

        if (append_character(&position, &remaining, '"') != 0 ||
            append_escaped_string(
                &position,
                &remaining,
                list[i]) != 0 ||
            append_character(&position, &remaining, '"') != 0) {
            goto failure;
        }
    }

    if (count == 1 &&
        append_character(&position, &remaining, ',') != 0) {
        goto failure;
    }

    if (append_character(&position, &remaining, ')') != 0) {
        goto failure;
    }

    *position = '\0';
    return tuple;

failure:
    {
        int saved_errno = errno;
        free(tuple);
        errno = saved_errno != 0 ? saved_errno : EOVERFLOW;
    }
    return NULL;
}

int main(int argc, char *argv[const])
{
    size_t count = argc > 1 ? (size_t)(argc - 1) : 0;
    char *tuple = string_list_to_tuple(
        (const char *const *)(argv + 1),
        count);

    if (tuple == NULL) {
        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    errno = 0;

    if (fputs(tuple, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        int saved_errno = errno != 0 ? errno : EIO;

        free(tuple);
        errno = saved_errno;
        perror("output");
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}