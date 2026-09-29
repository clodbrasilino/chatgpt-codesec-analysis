#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *const *items;
    size_t count;
} Tuple;

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuffer;

static int buffer_init(StringBuffer *buffer)
{
    buffer->data = malloc(1);
    if (buffer->data == NULL) {
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

    if (additional > SIZE_MAX - buffer->length - 1) {
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
        return 0;
    }

    buffer->data = new_data;
    buffer->capacity = capacity;
    return 1;
}

static int buffer_append(StringBuffer *buffer, const char *text)
{
    size_t length;

    if (text == NULL) {
        errno = EINVAL;
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(text);
    if (!buffer_reserve(buffer, length)) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer->data + buffer->length, text, length + 1);
    buffer->length += length;
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

static int buffer_append_quoted(StringBuffer *buffer, const char *text)
{
    static const char hexadecimal[] = "0123456789abcdef";
    const unsigned char *current;

    if (text == NULL) {
        errno = EINVAL;
        return 0;
    }

    if (!buffer_append_char(buffer, '"')) {
        return 0;
    }

    for (current = (const unsigned char *)text; *current != '\0'; ++current) {
        switch (*current) {
            case '"':
                if (!buffer_append(buffer, "\\\"")) {
                    return 0;
                }
                break;
            case '\\':
                if (!buffer_append(buffer, "\\\\")) {
                    return 0;
                }
                break;
            case '\b':
                if (!buffer_append(buffer, "\\b")) {
                    return 0;
                }
                break;
            case '\f':
                if (!buffer_append(buffer, "\\f")) {
                    return 0;
                }
                break;
            case '\n':
                if (!buffer_append(buffer, "\\n")) {
                    return 0;
                }
                break;
            case '\r':
                if (!buffer_append(buffer, "\\r")) {
                    return 0;
                }
                break;
            case '\t':
                if (!buffer_append(buffer, "\\t")) {
                    return 0;
                }
                break;
            default:
                if (*current < 0x20U) {
                    /* Possible weaknesses found:
                     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                     *  Variable 'escape' can be declared as const array [constVariable]
                     */
                    char escape[7] = {
                        '\\', 'u', '0', '0',
                        hexadecimal[*current >> 4],
                        hexadecimal[*current & 0x0FU],
                        '\0'
                    };

                    if (!buffer_append(buffer, escape)) {
                        return 0;
                    }
                } else if (!buffer_append_char(buffer, (char)*current)) {
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
        if (tuples[tuple_index].items == NULL && tuples[tuple_index].count != 0) {
            errno = EINVAL;
            free(buffer.data);
            return NULL;
        }

        if (tuple_index != 0 && !buffer_append(&buffer, ", ")) {
            free(buffer.data);
            return NULL;
        }

        if (!buffer_append_char(&buffer, '(')) {
            free(buffer.data);
            return NULL;
        }

        for (item_index = 0; item_index < tuples[tuple_index].count; ++item_index) {
            if (item_index != 0 && !buffer_append(&buffer, ", ")) {
                free(buffer.data);
                return NULL;
            }

            if (!buffer_append_quoted(
                    &buffer,
                    tuples[tuple_index].items[item_index])) {
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
    static const char *const first[] = {"Alice", "Engineer"};
    static const char *const second[] = {"Bob", "Manager"};
    static const char *const third[] = {"Carol", "Developer"};
    static const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    char *flattened;

    flattened = flatten_tuple_list(tuples, sizeof(tuples) / sizeof(tuples[0]));
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