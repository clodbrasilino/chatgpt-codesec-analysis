#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_add_size(size_t *const total, const size_t amount)
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

static size_t escaped_character_length(const unsigned char character)
{
    switch (character) {
        case '"':
        case '\\':
        case '\n':
        case '\r':
        case '\t':
        case '\b':
        case '\f':
            return 2U;

        default:
            return character < 0x20U || character == 0x7fU ? 4U : 1U;
    }
}

static char hexadecimal_digit(const unsigned int value)
{
    return value < 10U
        ? (char)('0' + value)
        : (char)('a' + value - 10U);
}

static int append_character(
    char **const destination,
    size_t *const remaining,
    const char character)
{
    if (destination == NULL || remaining == NULL || *destination == NULL) {
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
    char **const destination,
    size_t *const remaining,
    const char first,
    const char second)
{
    if (destination == NULL || remaining == NULL || *destination == NULL) {
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
    *remaining -= 2U;

    return 0;
}

static int append_hex_escape(
    char **const destination,
    size_t *const remaining,
    const unsigned char character)
{
    if (destination == NULL || remaining == NULL || *destination == NULL) {
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
    *remaining -= 4U;

    return 0;
}

static int measure_escaped_string(
    const char *source,
    size_t *const required_size)
{
    if (source == NULL || required_size == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (*source != '\0') {
        const unsigned char character = (unsigned char)*source;

        if (checked_add_size(
                required_size,
                escaped_character_length(character)) != 0) {
            return -1;
        }

        ++source;
    }

    return 0;
}

static int append_escaped_string(
    char **const destination,
    size_t *const remaining,
    const char *source)
{
    if (destination == NULL ||
        remaining == NULL ||
        *destination == NULL ||
        source == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (*source != '\0') {
        const unsigned char character = (unsigned char)*source;
        ++source;

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

static char *string_list_to_tuple(
    char *const *const list,
    const size_t count)
{
    size_t required_size = 3U;
    char *tuple;
    char *position;
    size_t remaining;

    if (count != 0U && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i != 0U && checked_add_size(&required_size, 2U) != 0) {
            return NULL;
        }

        if (checked_add_size(&required_size, 2U) != 0 ||
            measure_escaped_string(list[i], &required_size) != 0) {
            return NULL;
        }
    }

    if (count == 1U && checked_add_size(&required_size, 1U) != 0) {
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

    for (size_t i = 0U; i < count; ++i) {
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
        const int saved_errno = errno != 0 ? errno : EOVERFLOW;
        free(tuple);
        errno = saved_errno;
    }

    return NULL;
}

int main(int argc, char **const argv)
{
    const size_t count = argc > 1 ? (size_t)(argc - 1) : 0U;
    char *tuple = string_list_to_tuple(
        count == 0U ? NULL : argv + 1,
        count);

    if (tuple == NULL) {
        if (errno == 0) {
            errno = EINVAL;
        }

        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    if (fputs(tuple, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        const int saved_errno = errno != 0 ? errno : EIO;
        free(tuple);
        errno = saved_errno;
        perror("output");
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}