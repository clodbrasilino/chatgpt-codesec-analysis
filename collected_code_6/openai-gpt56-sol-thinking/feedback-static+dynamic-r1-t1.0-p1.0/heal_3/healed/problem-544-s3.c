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

static void buffer_destroy(StringBuffer *buffer)
{
    if (buffer == NULL) {
        return;
    }

    free(buffer->data);
    buffer->data = NULL;
    buffer->length = 0;
    buffer->capacity = 0;
}

static int buffer_reserve(StringBuffer *buffer, size_t additional)
{
    size_t required;
    size_t capacity;
    char *new_data;

    if (buffer == NULL || buffer->data == NULL ||
        buffer->length >= buffer->capacity) {
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

static int buffer_append_char(StringBuffer *buffer, char character)
{
    if (!buffer_reserve(buffer, 1)) {
        return 0;
    }

    buffer->data[buffer->length] = character;
    ++buffer->length;
    buffer->data[buffer->length] = '\0';
    return 1;
}

static int buffer_append_two(
    StringBuffer *buffer,
    char first,
    char second)
{
    size_t offset;

    if (!buffer_reserve(buffer, 2)) {
        return 0;
    }

    offset = buffer->length;
    buffer->data[offset] = first;
    buffer->data[offset + 1] = second;
    buffer->length += 2;
    buffer->data[buffer->length] = '\0';
    return 1;
}

static char hexadecimal_digit(unsigned int value)
{
    if (value < 10U) {
        return (char)('0' + value);
    }

    return (char)('a' + value - 10U);
}

static int buffer_append_control_escape(
    StringBuffer *buffer,
    unsigned char character)
{
    size_t offset;

    if (!buffer_reserve(buffer, 6)) {
        return 0;
    }

    offset = buffer->length;
    buffer->data[offset] = '\\';
    buffer->data[offset + 1] = 'u';
    buffer->data[offset + 2] = '0';
    buffer->data[offset + 3] = '0';
    buffer->data[offset + 4] =
        hexadecimal_digit((unsigned int)character >> 4);
    buffer->data[offset + 5] =
        hexadecimal_digit((unsigned int)character & 0x0FU);

    buffer->length += 6;
    buffer->data[buffer->length] = '\0';
    return 1;
}

static int buffer_append_quoted(
    StringBuffer *buffer,
    const StringView *text)
{
    size_t index;

    if (buffer == NULL || text == NULL ||
        (text->data == NULL && text->length != 0)) {
        errno = EINVAL;
        return 0;
    }

    if (!buffer_append_char(buffer, '"')) {
        return 0;
    }

    for (index = 0; index < text->length; ++index) {
        unsigned char character = (unsigned char)text->data[index];

        switch (character) {
            case '"':
                if (!buffer_append_two(buffer, '\\', '"')) {
                    return 0;
                }
                break;

            case '\\':
                if (!buffer_append_two(buffer, '\\', '\\')) {
                    return 0;
                }
                break;

            case '\b':
                if (!buffer_append_two(buffer, '\\', 'b')) {
                    return 0;
                }
                break;

            case '\f':
                if (!buffer_append_two(buffer, '\\', 'f')) {
                    return 0;
                }
                break;

            case '\n':
                if (!buffer_append_two(buffer, '\\', 'n')) {
                    return 0;
                }
                break;

            case '\r':
                if (!buffer_append_two(buffer, '\\', 'r')) {
                    return 0;
                }
                break;

            case '\t':
                if (!buffer_append_two(buffer, '\\', 't')) {
                    return 0;
                }
                break;

            default:
                if (character < 0x20U) {
                    if (!buffer_append_control_escape(buffer, character)) {
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
    int saved_errno;

    if (tuples == NULL && tuple_count != 0) {
        errno = EINVAL;
        return NULL;
    }

    if (!buffer_init(&buffer)) {
        return NULL;
    }

    if (!buffer_append_char(&buffer, '[')) {
        goto failure;
    }

    for (tuple_index = 0; tuple_index < tuple_count; ++tuple_index) {
        const Tuple *tuple = &tuples[tuple_index];

        if (tuple->items == NULL && tuple->count != 0) {
            errno = EINVAL;
            goto failure;
        }

        if (tuple_index != 0 &&
            !buffer_append_two(&buffer, ',', ' ')) {
            goto failure;
        }

        if (!buffer_append_char(&buffer, '(')) {
            goto failure;
        }

        for (item_index = 0; item_index < tuple->count; ++item_index) {
            if (item_index != 0 &&
                !buffer_append_two(&buffer, ',', ' ')) {
                goto failure;
            }

            if (!buffer_append_quoted(
                    &buffer,
                    &tuple->items[item_index])) {
                goto failure;
            }
        }

        if (!buffer_append_char(&buffer, ')')) {
            goto failure;
        }
    }

    if (!buffer_append_char(&buffer, ']')) {
        goto failure;
    }

    return buffer.data;

failure:
    saved_errno = errno;
    buffer_destroy(&buffer);
    errno = saved_errno;
    return NULL;
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

    char *flattened = flatten_tuple_list(
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