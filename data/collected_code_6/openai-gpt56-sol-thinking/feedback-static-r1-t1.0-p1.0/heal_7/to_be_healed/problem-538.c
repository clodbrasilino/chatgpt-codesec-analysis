#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} input_string;

typedef struct {
    char *position;
    size_t remaining;
} output_buffer;

static int checked_add_size(size_t *value, size_t increment)
{
    if (value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (increment > SIZE_MAX - *value) {
        errno = EOVERFLOW;
        return -1;
    }

    *value += increment;
    return 0;
}

static size_t escaped_character_size(unsigned char character)
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

static int append_two_characters(
    output_buffer *output,
    char first,
    char second
)
{
    if (append_character(output, first) != 0 ||
        append_character(output, second) != 0) {
        return -1;
    }

    return 0;
}

static int append_hexadecimal_escape(
    output_buffer *output,
    unsigned char character
)
{
    if (append_character(output, '\\') != 0 ||
        append_character(output, 'x') != 0 ||
        append_character(
            output,
            hexadecimal_digit((unsigned int)character >> 4U)
        ) != 0 ||
        append_character(
            output,
            hexadecimal_digit((unsigned int)character & 0x0fU)
        ) != 0) {
        return -1;
    }

    return 0;
}

static int append_escaped_string(
    output_buffer *output,
    const char *source,
    size_t source_length
)
{
    if (output == NULL || (source == NULL && source_length != 0U)) {
        errno = EINVAL;
        return -1;
    }

    for (size_t i = 0U; i < source_length; ++i) {
        unsigned char character = (unsigned char)source[i];

        switch (character) {
            case '"':
                if (append_two_characters(output, '\\', '"') != 0) {
                    return -1;
                }
                break;

            case '\\':
                if (append_two_characters(output, '\\', '\\') != 0) {
                    return -1;
                }
                break;

            case '\n':
                if (append_two_characters(output, '\\', 'n') != 0) {
                    return -1;
                }
                break;

            case '\r':
                if (append_two_characters(output, '\\', 'r') != 0) {
                    return -1;
                }
                break;

            case '\t':
                if (append_two_characters(output, '\\', 't') != 0) {
                    return -1;
                }
                break;

            case '\b':
                if (append_two_characters(output, '\\', 'b') != 0) {
                    return -1;
                }
                break;

            case '\f':
                if (append_two_characters(output, '\\', 'f') != 0) {
                    return -1;
                }
                break;

            default:
                if (character < 0x20U || character == 0x7fU) {
                    if (append_hexadecimal_escape(output, character) != 0) {
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

static int calculate_tuple_size(
    const input_string *list,
    size_t count,
    size_t *required_size
)
{
    size_t total = 3U;

    if (required_size == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (count != 0U && list == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (list[i].data == NULL && list[i].length != 0U) {
            errno = EINVAL;
            return -1;
        }

        if (i != 0U && checked_add_size(&total, 2U) != 0) {
            return -1;
        }

        if (checked_add_size(&total, 2U) != 0) {
            return -1;
        }

        for (size_t j = 0U; j < list[i].length; ++j) {
            if (checked_add_size(
                    &total,
                    escaped_character_size((unsigned char)list[i].data[j])
                ) != 0) {
                return -1;
            }
        }
    }

    if (count == 1U && checked_add_size(&total, 1U) != 0) {
        return -1;
    }

    *required_size = total;
    return 0;
}

static char *string_list_to_tuple(
    const input_string *list,
    size_t count
)
{
    size_t required_size;
    char *tuple;
    output_buffer output;

    if (calculate_tuple_size(list, count, &required_size) != 0) {
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
        if (i != 0U &&
            append_two_characters(&output, ',', ' ') != 0) {
            goto failure;
        }

        if (append_character(&output, '"') != 0 ||
            append_escaped_string(
                &output,
                list[i].data,
                list[i].length
            ) != 0 ||
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
    input_string *list = NULL;
    char *tuple;

    if (count != 0U) {
        if (count > SIZE_MAX / sizeof(*list)) {
            errno = EOVERFLOW;
            perror("input");
            return EXIT_FAILURE;
        }

        list = malloc(count * sizeof(*list));
        if (list == NULL) {
            errno = ENOMEM;
            perror("input");
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < count; ++i) {
            list[i].data = argv[i + 1U];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            list[i].length = strlen(argv[i + 1U]);
        }
    }

    tuple = string_list_to_tuple(list, count);
    free(list);

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