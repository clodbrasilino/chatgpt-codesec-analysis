#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    const StringView *items;
    size_t count;
} Tuple;

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuffer;

static int buffer_init(StringBuffer *buffer)
{
    if (buffer == NULL) {
        errno = EINVAL;
        return 0;
    }

    buffer->data = malloc(1);
    if (buffer->data == NULL) {
        errno = ENOMEM;
        return 0;
    }

    buffer->data[0] = '\0';
    buffer->length = 0;
    buffer->capacity = 1;
    return 1;
}

static int buffer_reserve(StringBuffer *buffer, size_t additional)
{
    size_t required;
    size_t capacity;
    char *new_data;

    if (buffer == NULL || buffer->data == NULL) {
        errno = EINVAL;
        return 0;
    }

    if (buffer->length == SIZE_MAX ||
        additional > SIZE_MAX - buffer->length - 1) {
        errno = EOVERFLOW;
        return 0;
    }

    required = buffer->length + additional + 1;
    if (required <= buffer->capacity) {
        return 1;
    }

    capacity = buffer->capacity;
    while (capacity < required) {
        if (capacity > SIZE_MAX / 2) {
            capacity = required;
            break;
        }

        capacity *= 2;
    }

    new_data = realloc(buffer->data, capacity);
    if (new_data == NULL) {
        errno = ENOMEM;
        return 0;
    }

    buffer->data = new_data;
    buffer->capacity = capacity;
    return 1;
}

static int buffer_append_n(
    StringBuffer *buffer,
    const char *text,
    size_t text_length)
{
    size_t index;

    if (text == NULL && text_length != 0) {
        errno = EINVAL;
        return 0;
    }

    if (!buffer_reserve(buffer, text_length)) {
        return 0;
    }

    for (index = 0; index < text_length; ++index) {
        buffer->data[buffer->length + index] = text[index];
    }

    buffer->length += text_length;
    buffer->data[buffer->length] = '\0';
    return 1;
}

static int buffer_append_char(StringBuffer *buffer, char character)
{
    if (!buffer_reserve(buffer, 1)) {
        return 0;
    }

    buffer->data[buffer->length++] = character;
    buffer->data[buffer->length] = '\0';
    return 1;
}

static int buffer_append_quoted(
    StringBuffer *buffer,
    const char *text,
    size_t text_length)
{
    static const char hexadecimal[] = "0123456789abcdef";
    size_t index;

    if (text == NULL) {
        errno = EINVAL;
        return 0;
    }

    if (!buffer_append_char(buffer, '"')) {
        return 0;
    }

    for (index = 0; index < text_length; ++index) {
        unsigned char character = (unsigned char)text[index];

        switch (character) {
            case '"':
                if (!buffer_append_n(buffer, "\\\"", 2)) {
                    return 0;
                }
                break;

            case '\\':
                if (!buffer_append_n(buffer, "\\\\", 2)) {
                    return 0;
                }
                break;

            case '\b':
                if (!buffer_append_n(buffer, "\\b", 2)) {
                    return 0;
                }
                break;

            case '\f':
                if (!buffer_append_n(buffer, "\\f", 2)) {
                    return 0;
                }
                break;

            case '\n':
                if (!buffer_append_n(buffer, "\\n", 2)) {
                    return 0;
                }
                break;

            case '\r':
                if (!buffer_append_n(buffer, "\\r", 2)) {
                    return 0;
                }
                break;

            case '\t':
                if (!buffer_append_n(buffer, "\\t", 2)) {
                    return 0;
                }
                break;

            default:
                if (character < 0x20U) {
                    if (!buffer_append_n(buffer, "\\u00", 4) ||
                        !buffer_append_char(
                            buffer,
                            hexadecimal[character >> 4]) ||
                        !buffer_append_char(
                            buffer,
                            hexadecimal[character & 0x0FU])) {
                        return 0;
                    }
                } else if (!buffer_append_char(buffer, (char)character)) {
                    return 0;
                }
                break;
        }
    }

    return buffer_append_char(buffer, '"');
}

char *flatten_tuple_list(const Tuple *tuples, size_t tuple_count)
{
    StringBuffer buffer;
    size_t tuple_index;
    size_t item_index;

    if (tuples == NULL && tuple_count != 0) {
        errno = EINVAL;
        return NULL;
    }

    if (!buffer_init(&buffer)) {
        return NULL;
    }

    if (!buffer_append_char(&buffer, '[')) {
        free(buffer.data);
        return NULL;
    }

    for (tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
        if (tuples[tuple_index].items == NULL &&
            tuples[tuple_index].count != 0) {
            errno = EINVAL;
            free(buffer.data);
            return NULL;
        }

        if (tuple_index != 0 &&
            !buffer_append_n(&buffer, ", ", 2)) {
            free(buffer.data);
            return NULL;
        }

        if (!buffer_append_char(&buffer, '(')) {
            free(buffer.data);
            return NULL;
        }

        for (item_index = 0;
             item_index < tuples[tuple_index].count;
             ++item_index) {
            const StringView *item =
                &tuples[tuple_index].items[item_index];

            if (item_index != 0 &&
                !buffer_append_n(&buffer, ", ", 2)) {
                free(buffer.data);
                return NULL;
            }

            if (!buffer_append_quoted(
                    &buffer,
                    item->data,
                    item->length)) {
                free(buffer.data);
                return NULL;
            }
        }

        if (!buffer_append_char(&buffer, ')')) {
            free(buffer.data);
            return NULL;
        }
    }

    if (!buffer_append_char(&buffer, ']')) {
        free(buffer.data);
        return NULL;
    }

    return buffer.data;
}

int main(void)
{
    static const StringView first[] = {
        {"Alice", sizeof("Alice") - 1},
        {"Engineer", sizeof("Engineer") - 1}
    };
    static const StringView second[] = {
        {"Bob", sizeof("Bob") - 1},
        {"Manager", sizeof("Manager") - 1}
    };
    static const StringView third[] = {
        {"Carol", sizeof("Carol") - 1},
        {"Developer", sizeof("Developer") - 1}
    };
    static const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    char *flattened;

    flattened = flatten_tuple_list(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]));

    if (flattened == NULL) {
        perror("flatten_tuple_list");
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}