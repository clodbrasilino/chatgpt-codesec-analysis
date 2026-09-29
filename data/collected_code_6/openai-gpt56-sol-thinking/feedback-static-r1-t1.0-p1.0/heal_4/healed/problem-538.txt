#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *position;
    size_t remaining;
} output_buffer;

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
            return character < 0x20U || character == 0x7fU ? 4U : 1U;
    }
}

static char hexadecimal_digit(unsigned int value)
{
    return (char)(value < 10U
                      ? (unsigned int)'0' + value
                      : (unsigned int)'a' + value - 10U);
}

static int append_character(output_buffer *output, char character)
{
    if (output == NULL || output->position == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (output->remaining == 0U) {
        errno = EOVERFLOW;
        return -1;
    }

    *output->position++ = character;
    --output->remaining;
    return 0;
}

static int append_escaped_string(output_buffer *output, const char *source)
{
    if (output == NULL || source == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        switch (character) {
            case '"':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, '"') != 0) {
                    return -1;
                }
                break;

            case '\\':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, '\\') != 0) {
                    return -1;
                }
                break;

            case '\n':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, 'n') != 0) {
                    return -1;
                }
                break;

            case '\r':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, 'r') != 0) {
                    return -1;
                }
                break;

            case '\t':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, 't') != 0) {
                    return -1;
                }
                break;

            case '\b':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, 'b') != 0) {
                    return -1;
                }
                break;

            case '\f':
                if (append_character(output, '\\') != 0 ||
                    append_character(output, 'f') != 0) {
                    return -1;
                }
                break;

            default:
                if (character < 0x20U || character == 0x7fU) {
                    if (append_character(output, '\\') != 0 ||
                        append_character(output, 'x') != 0 ||
                        append_character(
                            output,
                            hexadecimal_digit((unsigned int)character >> 4)
                        ) != 0 ||
                        append_character(
                            output,
                            hexadecimal_digit((unsigned int)character & 0x0fU)
                        ) != 0) {
                        return -1;
                    }
                } else if (append_character(output, (char)character) != 0) {
                    return -1;
                }
                break;
        }
    }

    return 0;
}

static char *string_list_to_tuple(char *const *list, size_t count)
{
    size_t required_size = 3U;
    char *tuple;
    output_buffer output;

    if (count != 0U && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0U; i < count; ++i) {
        const unsigned char *current;

        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i != 0U && add_size(&required_size, 2U) != 0) {
            return NULL;
        }

        if (add_size(&required_size, 2U) != 0) {
            return NULL;
        }

        current = (const unsigned char *)list[i];

        while (*current != '\0') {
            if (add_size(
                    &required_size,
                    escaped_character_length(*current)
                ) != 0) {
                return NULL;
            }

            ++current;
        }
    }

    if (count == 1U && add_size(&required_size, 1U) != 0) {
        return NULL;
    }

    tuple = malloc(required_size);
    if (tuple == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    output.position = tuple;
    output.remaining = required_size;

    if (append_character(&output, '(') != 0) {
        goto failure;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (i != 0U) {
            if (append_character(&output, ',') != 0 ||
                append_character(&output, ' ') != 0) {
                goto failure;
            }
        }

        if (append_character(&output, '"') != 0 ||
            append_escaped_string(&output, list[i]) != 0 ||
            append_character(&output, '"') != 0) {
            goto failure;
        }
    }

    if (count == 1U && append_character(&output, ',') != 0) {
        goto failure;
    }

    if (append_character(&output, ')') != 0) {
        goto failure;
    }

    if (output.remaining != 1U) {
        errno = EOVERFLOW;
        goto failure;
    }

    if (append_character(&output, '\0') != 0) {
        goto failure;
    }

    return tuple;

failure:
    {
        int saved_errno = errno;
        free(tuple);
        errno = saved_errno;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    size_t count = argc > 1 ? (size_t)(argc - 1) : 0U;
    char *tuple = string_list_to_tuple(
        count == 0U ? NULL : argv + 1,
        count
    );

    if (tuple == NULL) {
        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    errno = 0;

    if (fputs(tuple, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        int saved_errno = errno;

        if (saved_errno == 0) {
            saved_errno = EIO;
        }

        free(tuple);
        errno = saved_errno;
        perror("output");
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}