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
        int integer;
        char *string;
    } data;
} Value;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    if (length != 0U && memchr(source, '\0', length) != NULL) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int compare_values(const void *left_pointer, const void *right_pointer)
{
    const Value *left = left_pointer;
    const Value *right = right_pointer;

    if (left->type != right->type) {
        return left->type == VALUE_INTEGER ? -1 : 1;
    }

    switch (left->type) {
    case VALUE_INTEGER:
        return (left->data.integer > right->data.integer) -
               (left->data.integer < right->data.integer);

    case VALUE_STRING:
        if (left->data.string == NULL) {
            return right->data.string == NULL ? 0 : -1;
        }

        if (right->data.string == NULL) {
            return 1;
        }

        return strcmp(left->data.string, right->data.string);

    default:
        return 0;
    }
}

static int sort_values(Value *values, size_t count)
{
    if (values == NULL && count != 0U) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    if (count > 1U) {
        qsort(values, count, sizeof(*values), compare_values);
    }

    return 0;
}

static void free_values(Value *values, size_t count)
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

static int initialize_values(Value **result, size_t *count)
{
    static const char strings[][7] = {
        "pear",
        "apple",
        "orange"
    };
    static const size_t string_lengths[] = {
        sizeof("pear") - 1U,
        sizeof("apple") - 1U,
        sizeof("orange") - 1U
    };
    static const int integers[] = {
        42,
        -7,
        10
    };

    const size_t integer_count = sizeof(integers) / sizeof(integers[0]);
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    size_t initialized_count = 0U;
    size_t total_count;
    size_t index;
    Value *values;

    if (result == NULL || count == NULL) {
        return -1;
    }

    *result = NULL;
    *count = 0U;

    if (string_count != sizeof(string_lengths) / sizeof(string_lengths[0])) {
        return -1;
    }

    if (integer_count > SIZE_MAX - string_count) {
        return -1;
    }

    total_count = integer_count + string_count;

    if (total_count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    values = calloc(total_count, sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (index = 0U; index < integer_count; ++index) {
        values[initialized_count].type = VALUE_INTEGER;
        values[initialized_count].data.integer = integers[index];
        ++initialized_count;
    }

    for (index = 0U; index < string_count; ++index) {
        size_t length = string_lengths[index];

        if (length >= sizeof(strings[index]) ||
            strings[index][length] != '\0' ||
            (length != 0U && memchr(strings[index], '\0', length) != NULL)) {
            free_values(values, initialized_count);
            return -1;
        }

        values[initialized_count].type = VALUE_STRING;
        values[initialized_count].data.string =
            duplicate_string(strings[index], length);

        if (values[initialized_count].data.string == NULL) {
            free_values(values, initialized_count + 1U);
            return -1;
        }

        ++initialized_count;
    }

    *result = values;
    *count = total_count;
    return 0;
}

int main(void)
{
    Value *values = NULL;
    size_t count = 0U;
    size_t index;

    if (initialize_values(&values, &count) != 0) {
        fputs("Failed to initialize values.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sort_values(values, count) != 0) {
        free_values(values, count);
        fputs("Failed to sort values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        int output_result;

        switch (values[index].type) {
        case VALUE_INTEGER:
            output_result = printf("%d\n", values[index].data.integer);
            break;

        case VALUE_STRING:
            if (values[index].data.string == NULL) {
                free_values(values, count);
                return EXIT_FAILURE;
            }

            output_result = puts(values[index].data.string);
            break;

        default:
            free_values(values, count);
            return EXIT_FAILURE;
        }

        if (output_result < 0) {
            free_values(values, count);
            return EXIT_FAILURE;
        }
    }

    free_values(values, count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}