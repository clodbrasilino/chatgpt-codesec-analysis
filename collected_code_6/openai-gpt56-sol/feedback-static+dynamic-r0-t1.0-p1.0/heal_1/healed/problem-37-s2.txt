#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_STRING
} ValueType;

typedef struct {
    ValueType type;
    union {
        long integer;
        char *string;
    } data;
} Value;

static int duplicate_string(const char *source, size_t source_size, char **output)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *output = copy;
    return 0;
}

static int compare_values(const void *left_ptr, const void *right_ptr)
{
    const Value *left = left_ptr;
    const Value *right = right_ptr;

    if (left->type != right->type) {
        return left->type < right->type ? -1 : 1;
    }

    if (left->type == VALUE_INTEGER) {
        if (left->data.integer < right->data.integer) {
            return -1;
        }
        if (left->data.integer > right->data.integer) {
            return 1;
        }
        return 0;
    }

    if (left->data.string == NULL && right->data.string == NULL) {
        return 0;
    }
    if (left->data.string == NULL) {
        return -1;
    }
    if (right->data.string == NULL) {
        return 1;
    }

    return strcmp(left->data.string, right->data.string);
}

static int sort_values(Value *values, size_t count)
{
    if (values == NULL && count != 0U) {
        return -1;
    }

    if (count > 1U) {
        qsort(values, count, sizeof(*values), compare_values);
    }

    return 0;
}

static void destroy_values(Value *values, size_t count)
{
    size_t index;

    if (values == NULL) {
        return;
    }

    for (index = 0U; index < count; ++index) {
        if (values[index].type == VALUE_STRING) {
            free(values[index].data.string);
            values[index].data.string = NULL;
        }
    }

    free(values);
}

static int initialize_values(Value **output, size_t *output_count)
{
    static const struct {
        ValueType type;
        long integer;
        const char *string;
        size_t string_size;
    } initial[] = {
        { VALUE_STRING, 0L, "pear", sizeof("pear") },
        { VALUE_INTEGER, 42L, NULL, 0U },
        { VALUE_STRING, 0L, "apple", sizeof("apple") },
        { VALUE_INTEGER, -7L, NULL, 0U },
        { VALUE_STRING, 0L, "orange", sizeof("orange") },
        { VALUE_INTEGER, 10L, NULL, 0U }
    };

    const size_t count = sizeof(initial) / sizeof(initial[0]);
    Value *values;
    size_t index;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    if (count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (index = 0U; index < count; ++index) {
        values[index].type = initial[index].type;

        if (initial[index].type == VALUE_INTEGER) {
            values[index].data.integer = initial[index].integer;
        } else if (initial[index].type == VALUE_STRING) {
            if (duplicate_string(initial[index].string,
                                 initial[index].string_size,
                                 &values[index].data.string) != 0) {
                destroy_values(values, count);
                return -1;
            }
        } else {
            destroy_values(values, count);
            return -1;
        }
    }

    *output = values;
    *output_count = count;
    return 0;
}

int main(void)
{
    Value *values = NULL;
    size_t count = 0U;
    size_t index;

    if (initialize_values(&values, &count) != 0) {
        fputs("Failed to initialize the list\n", stderr);
        return EXIT_FAILURE;
    }

    if (sort_values(values, count) != 0) {
        fputs("Failed to sort the list\n", stderr);
        destroy_values(values, count);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        int result;

        if (values[index].type == VALUE_INTEGER) {
            result = printf("%ld\n", values[index].data.integer);
        } else {
            result = printf("%s\n", values[index].data.string);
        }

        if (result < 0) {
            fputs("Failed to write output\n", stderr);
            destroy_values(values, count);
            return EXIT_FAILURE;
        }
    }

    destroy_values(values, count);
    return EXIT_SUCCESS;
}