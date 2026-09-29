#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilder;

char *camel_to_snake(const char *input);

static int builder_init(StringBuilder *builder, size_t initial_capacity)
{
    if (builder == NULL) {
        return 0;
    }

    builder->data = NULL;
    builder->length = 0U;
    builder->capacity = 0U;

    if (initial_capacity < 16U) {
        initial_capacity = 16U;
    }

    builder->data = malloc(initial_capacity);
    if (builder->data == NULL) {
        return 0;
    }

    builder->data[0] = '\0';
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

    if (builder->length == SIZE_MAX ||
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

static int builder_append(
    StringBuilder *builder,
    const char *source,
    size_t length)
{
    if (source == NULL || !builder_reserve(builder, length)) {
        return 0;
    }

    if (length != 0U) {
        memcpy(builder->data + builder->length, source, length);
        builder->length += length;
    }

    builder->data[builder->length] = '\0';
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

static char *insert_boundaries(const char *input, const regex_t *regex)
{
    StringBuilder builder;
    regmatch_t matches[3];
    size_t input_length;
    size_t offset;

    if (input == NULL || regex == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        return NULL;
    }

    if (!builder_init(&builder, input_length + 1U)) {
        return NULL;
    }

    offset = 0U;

    while (offset < input_length) {
        size_t remaining = input_length - offset;
        size_t match_end;
        size_t insertion_point;
        int status = regexec(regex, input + offset, 3U, matches, 0);

        if (status == REG_NOMATCH) {
            if (!builder_append(&builder, input + offset, remaining)) {
                builder_destroy(&builder);
                return NULL;
            }

            offset = input_length;
            break;
        }

        if (status != 0 ||
            matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[2].rm_so < matches[0].rm_so ||
            matches[2].rm_so > matches[0].rm_eo ||
            (uintmax_t)matches[0].rm_eo > (uintmax_t)remaining) {
            builder_destroy(&builder);
            return NULL;
        }

        match_end = (size_t)matches[0].rm_eo;
        insertion_point = (size_t)matches[2].rm_so;

        if (!builder_append(&builder, input + offset, insertion_point) ||
            !builder_append_char(&builder, '_') ||
            !builder_append(
                &builder,
                input + offset + insertion_point,
                match_end - insertion_point)) {
            builder_destroy(&builder);
            return NULL;
        }

        offset += match_end;
    }

    return builder.data;
}

char *camel_to_snake(const char *input)
{
    regex_t acronym_regex;
    regex_t camel_regex;
    char *intermediate;
    char *result;
    size_t index;

    if (input == NULL) {
        return NULL;
    }

    if (regcomp(
            &acronym_regex,
            "([A-Z]+)([A-Z][a-z])",
            REG_EXTENDED) != 0) {
        return NULL;
    }

    if (regcomp(
            &camel_regex,
            "([a-z0-9])([A-Z])",
            REG_EXTENDED) != 0) {
        regfree(&acronym_regex);
        return NULL;
    }

    intermediate = insert_boundaries(input, &acronym_regex);
    if (intermediate == NULL) {
        regfree(&camel_regex);
        regfree(&acronym_regex);
        return NULL;
    }

    result = insert_boundaries(intermediate, &camel_regex);
    free(intermediate);

    regfree(&camel_regex);
    regfree(&acronym_regex);

    if (result == NULL) {
        return NULL;
    }

    for (index = 0U; result[index] != '\0'; ++index) {
        result[index] = (char)tolower((unsigned char)result[index]);
    }

    return result;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    char *result;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "camel_to_snake";

    if (argc != 2) {
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