#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
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

    return strcmp(left->data.string, right->data.string);
}

static int sort_values(Value *values, size_t count)
{
    if (values == NULL && count != 0U) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_values);
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
    } initial[] = {
        {VALUE_STRING, 0L, "pear"},
        {VALUE_INTEGER, 42L, NULL},
        {VALUE_STRING, 0L, "apple"},
        {VALUE_INTEGER, -7L, NULL},
        {VALUE_STRING, 0L, "orange"},
        {VALUE_INTEGER, 10L, NULL}
    };

    const size_t count = sizeof(initial) / sizeof(initial[0]);
    Value *values;
    size_t index;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    for (index = 0U; index < count; ++index) {
        values[index].type = initial[index].type;

        if (initial[index].type == VALUE_INTEGER) {
            values[index].data.integer = initial[index].integer;
        } else {
            values[index].data.string = duplicate_string(initial[index].string);
            if (values[index].data.string == NULL) {
                destroy_values(values, count);
                return -1;
            }
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
        fprintf(stderr, "Failed to initialize the list: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (sort_values(values, count) != 0) {
        fprintf(stderr, "Failed to sort the list\n");
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
            fprintf(stderr, "Failed to write output\n");
            destroy_values(values, count);
            return EXIT_FAILURE;
        }
    }

    destroy_values(values, count);
    return EXIT_SUCCESS;
}