#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilder;

static int builder_init(StringBuilder *builder)
{
    const size_t initial_capacity = 16U;

    if (builder == NULL) {
        return 0;
    }

    builder->data = malloc(initial_capacity);
    if (builder->data == NULL) {
        builder->length = 0U;
        builder->capacity = 0U;
        return 0;
    }

    builder->data[0] = '\0';
    builder->length = 0U;
    builder->capacity = initial_capacity;
    return 1;
}

static void builder_destroy(StringBuilder *builder)
{
    if (builder == NULL) {
        return;
    }

    free(builder->data);
    builder->data = NULL;
    builder->length = 0U;
    builder->capacity = 0U;
}

static int builder_reserve(StringBuilder *builder, size_t additional)
{
    size_t required;
    size_t new_capacity;
    char *new_data;

    if (builder == NULL || builder->data == NULL) {
        return 0;
    }

    if (builder->length > SIZE_MAX - 1U ||
        additional > SIZE_MAX - builder->length - 1U) {
        return 0;
    }

    required = builder->length + additional + 1U;
    if (required <= builder->capacity) {
        return 1;
    }

    new_capacity = builder->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    new_data = realloc(builder->data, new_capacity);
    if (new_data == NULL) {
        return 0;
    }

    builder->data = new_data;
    builder->capacity = new_capacity;
    return 1;
}

static int builder_append_char(StringBuilder *builder, char value)
{
    if (!builder_reserve(builder, 1U)) {
        return 0;
    }

    builder->data[builder->length] = value;
    ++builder->length;
    builder->data[builder->length] = '\0';
    return 1;
}

static int is_ascii_upper(unsigned char value)
{
    return value >= (unsigned char)'A' && value <= (unsigned char)'Z';
}

static int is_ascii_lower(unsigned char value)
{
    return value >= (unsigned char)'a' && value <= (unsigned char)'z';
}

static int is_ascii_digit(unsigned char value)
{
    return value >= (unsigned char)'0' && value <= (unsigned char)'9';
}

char *camel_to_snake(const char *input)
{
    StringBuilder builder;
    const unsigned char *cursor;
    unsigned char previous = 0U;
    int has_previous = 0;

    if (input == NULL) {
        return NULL;
    }

    if (!builder_init(&builder)) {
        return NULL;
    }

    cursor = (const unsigned char *)input;

    while (*cursor != '\0') {
        unsigned char current = cursor[0];
        unsigned char next = cursor[1];
        int needs_boundary = 0;

        if (has_previous && is_ascii_upper(current)) {
            if (is_ascii_lower(previous) || is_ascii_digit(previous)) {
                needs_boundary = 1;
            } else if (is_ascii_upper(previous) && is_ascii_lower(next)) {
                needs_boundary = 1;
            }
        }

        if (needs_boundary && !builder_append_char(&builder, '_')) {
            builder_destroy(&builder);
            return NULL;
        }

        if (!builder_append_char(
                &builder,
                (char)tolower((int)current))) {
            builder_destroy(&builder);
            return NULL;
        }

        previous = current;
        has_previous = 1;
        ++cursor;
    }

    return builder.data;
}

int main(int argc, char *argv[])
{
    char *result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result);
    free(result);

    return EXIT_SUCCESS;
}