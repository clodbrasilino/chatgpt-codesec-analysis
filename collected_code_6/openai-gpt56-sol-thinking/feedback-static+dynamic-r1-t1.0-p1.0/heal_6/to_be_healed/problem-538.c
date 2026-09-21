#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_add_size(size_t *total, size_t amount)
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
            return character < 0x20U || character == 0x7fU ? 4 : 1;
    }
}

static char hexadecimal_digit(unsigned int value)
{
    return (char)(value < 10U
        ? (unsigned int)'0' + value
        : (unsigned int)'a' + value - 10U);
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

    if (*remaining < 1U) {
        errno = EOVERFLOW;
        return -1;
    }

    **destination = character;
    ++*destination;
    --*remaining;

    return 0;
}

static int append_pair(
    char **destination,
    size_t *remaining,
    char first,
    char second)
{
    if (destination == NULL || *destination == NULL || remaining == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*remaining < 2U) {
        errno = EOVERFLOW;
        return -1;
    }

    (*destination)[0] = first;
    (*destination)[1] = second;
    *destination += 2;
    *remaining -= 2;

    return 0;
}

static int append_hex_escape(
    char **destination,
    size_t *remaining,
    unsigned char character)
{
    if (destination == NULL || *destination == NULL || remaining == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*remaining < 4U) {
        errno = EOVERFLOW;
        return -1;
    }

    (*destination)[0] = '\\';
    (*destination)[1] = 'x';
    (*destination)[2] =
        hexadecimal_digit((unsigned int)character >> 4U);
    (*destination)[3] =
        hexadecimal_digit((unsigned int)character & 0x0fU);

    *destination += 4;
    *remaining -= 4;

    return 0;
}

static int append_escaped_string(
    char **destination,
    size_t *remaining,
    const char *source)
{
    if (destination == NULL || *destination == NULL ||
        remaining == NULL || source == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        switch (character) {
            case '"':
                if (append_pair(destination, remaining, '\\', '"') != 0) {
                    return -1;
                }
                break;

            case '\\':
                if (append_pair(destination, remaining, '\\', '\\') != 0) {
                    return -1;
                }
                break;

            case '\n':
                if (append_pair(destination, remaining, '\\', 'n') != 0) {
                    return -1;
                }
                break;

            case '\r':
                if (append_pair(destination, remaining, '\\', 'r') != 0) {
                    return -1;
                }
                break;

            case '\t':
                if (append_pair(destination, remaining, '\\', 't') != 0) {
                    return -1;
                }
                break;

            case '\b':
                if (append_pair(destination, remaining, '\\', 'b') != 0) {
                    return -1;
                }
                break;

            case '\f':
                if (append_pair(destination, remaining, '\\', 'f') != 0) {
                    return -1;
                }
                break;

            default:
                if (character < 0x20U || character == 0x7fU) {
                    if (append_hex_escape(
                            destination,
                            remaining,
                            character) != 0) {
                        return -1;
                    }
                } else {
                    if (append_character(
                            destination,
                            remaining,
                            (char)character) != 0) {
                        return -1;
                    }
                }
                break;
        }
    }

    return 0;
}

char *string_list_to_tuple(
    const char *const list[],
    size_t count)
{
    size_t required_size = 3U;
    char *tuple;
    char *position;
    size_t remaining;

    if (count != 0U && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const unsigned char *current;

        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i != 0U &&
            checked_add_size(&required_size, 2U) != 0) {
            return NULL;
        }

        if (checked_add_size(&required_size, 2U) != 0) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        current = (const unsigned char *)list[i];

        while (*current != '\0') {
            if (checked_add_size(
                    &required_size,
                    escaped_character_length(*current)) != 0) {
                return NULL;
            }

            ++current;
        }
    }

    if (count == 1U &&
        checked_add_size(&required_size, 1U) != 0) {
        return NULL;
    }

    tuple = malloc(required_size);
    if (tuple == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    position = tuple;
    remaining = required_size;

    if (append_character(&position, &remaining, '(') != 0) {
        goto failure;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i != 0U &&
            append_pair(&position, &remaining, ',', ' ') != 0) {
            goto failure;
        }

        if (append_character(&position, &remaining, '"') != 0 ||
            append_escaped_string(&position, &remaining, list[i]) != 0 ||
            append_character(&position, &remaining, '"') != 0) {
            goto failure;
        }
    }

    if (count == 1U &&
        append_character(&position, &remaining, ',') != 0) {
        goto failure;
    }

    if (append_character(&position, &remaining, ')') != 0 ||
        append_character(&position, &remaining, '\0') != 0) {
        goto failure;
    }

    if (remaining != 0U) {
        errno = EOVERFLOW;
        goto failure;
    }

    return tuple;

failure:
    {
        int saved_errno = errno != 0 ? errno : EOVERFLOW;
        free(tuple);
        errno = saved_errno;
    }

    return NULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    size_t count = argc > 1 ? (size_t)(argc - 1) : 0U;
    const char **arguments = NULL;
    char *tuple;

    if (count != 0U) {
        if (count > SIZE_MAX / sizeof(*arguments)) {
            errno = EOVERFLOW;
            perror("arguments");
            return EXIT_FAILURE;
        }

        arguments = malloc(count * sizeof(*arguments));
        if (arguments == NULL) {
            errno = ENOMEM;
            perror("arguments");
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < count; ++i) {
            arguments[i] = argv[i + 1U];
        }
    }

    tuple = string_list_to_tuple(arguments, count);
    if (tuple == NULL) {
        int saved_errno = errno != 0 ? errno : EINVAL;
        free(arguments);
        errno = saved_errno;
        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    free(arguments);

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