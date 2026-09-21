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

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static int compare_values(const void *left_ptr, const void *right_ptr)
{
    const Value *left = left_ptr;
    const Value *right = right_ptr;

    if (left->type != right->type) {
        return left->type == VALUE_INTEGER ? -1 : 1;
    }

    if (left->type == VALUE_INTEGER) {
        return (left->data.integer > right->data.integer) -
               (left->data.integer < right->data.integer);
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
    static const int integers[] = {
        42,
        -7,
        10
    };
    const size_t integer_count = sizeof(integers) / sizeof(integers[0]);
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    size_t total_count;
    Value *values;
    size_t index;

    if (result == NULL || count == NULL) {
        return -1;
    }

    *result = NULL;
    *count = 0U;

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
        values[index].type = VALUE_INTEGER;
        values[index].data.integer = integers[index];
    }

    for (index = 0U; index < string_count; ++index) {
        size_t destination = integer_count + index;

        values[destination].type = VALUE_STRING;
        values[destination].data.string =
            duplicate_string(strings[index], sizeof(strings[index]));

        if (values[destination].data.string == NULL) {
            free_values(values, destination + 1U);
            return -1;
        }
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
        (void)fputs("Failed to initialize values.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sort_values(values, count) != 0) {
        free_values(values, count);
        (void)fputs("Failed to sort values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        int print_result;

        if (values[index].type == VALUE_INTEGER) {
            print_result = printf("%d\n", values[index].data.integer);
        } else if (values[index].type == VALUE_STRING &&
                   values[index].data.string != NULL) {
            print_result = printf("%s\n", values[index].data.string);
        } else {
            free_values(values, count);
            return EXIT_FAILURE;
        }

        if (print_result < 0) {
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