#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    const StringView *elements;
    size_t count;
} Tuple;

typedef struct {
    char *data;
    size_t length;
} String;

static void free_string_array(String *strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i].data);
    }

    free(strings);
}

static int copy_bytes(char *destination,
                      size_t destination_capacity,
                      size_t offset,
                      const char *source,
                      size_t source_length)
{
    if (destination == NULL) {
        return -1;
    }

    if (source_length > 0 && source == NULL) {
        return -1;
    }

    if (offset > destination_capacity ||
        source_length > destination_capacity - offset) {
        return -1;
    }

    for (size_t i = 0; i < source_length; ++i) {
        destination[offset + i] = source[i];
    }

    return 0;
}

static int concatenate_adjacent(const Tuple *tuple,
                                String **result,
                                size_t *result_count)
{
    String *concatenated;
    size_t adjacent_count;

    if (tuple == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple->count > 0 && tuple->elements == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i].length > 0 &&
            tuple->elements[i].data == NULL) {
            return -1;
        }
    }

    if (tuple->count < 2) {
        return 0;
    }

    adjacent_count = tuple->count - 1;

    if (adjacent_count > SIZE_MAX / sizeof(*concatenated)) {
        return -1;
    }

    concatenated = calloc(adjacent_count, sizeof(*concatenated));
    if (concatenated == NULL) {
        return -1;
    }

    for (size_t i = 0; i < adjacent_count; ++i) {
        const StringView *first = &tuple->elements[i];
        const StringView *second = &tuple->elements[i + 1];
        size_t combined_length;
        size_t capacity;

        if (first->length > SIZE_MAX - second->length) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        combined_length = first->length + second->length;

        if (combined_length == SIZE_MAX) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        capacity = combined_length + 1;
        concatenated[i].data = malloc(capacity);
        if (concatenated[i].data == NULL) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        if (copy_bytes(concatenated[i].data,
                       capacity,
                       0,
                       first->data,
                       first->length) != 0 ||
            copy_bytes(concatenated[i].data,
                       capacity,
                       first->length,
                       second->data,
                       second->length) != 0) {
            free_string_array(concatenated, adjacent_count);
            return -1;
        }

        concatenated[i].data[combined_length] = '\0';
        concatenated[i].length = combined_length;
    }

    *result = concatenated;
    *result_count = adjacent_count;
    return 0;
}

static int print_string_tuple(const String *strings, size_t count)
{
    if (count > 0 && strings == NULL) {
        return -1;
    }

    if (fputc('(', stdout) == EOF) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i].length > 0 && strings[i].data == NULL) {
            return -1;
        }

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('"', stdout) == EOF) {
            return -1;
        }

        if (strings[i].length > 0 &&
            fwrite(strings[i].data,
                   1,
                   strings[i].length,
                   stdout) != strings[i].length) {
            return -1;
        }

        if (fputc('"', stdout) == EOF) {
            return -1;
        }
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const StringView first_elements[] = {
        {"GFG", sizeof("GFG") - 1},
        {"is", sizeof("is") - 1},
        {"best", sizeof("best") - 1},
        {"for", sizeof("for") - 1},
        {"geeks", sizeof("geeks") - 1}
    };

    const StringView second_elements[] = {
        {"C", sizeof("C") - 1},
        {"programming", sizeof("programming") - 1},
        {"is", sizeof("is") - 1},
        {"powerful", sizeof("powerful") - 1}
    };

    const Tuple tuples[] = {
        {
            first_elements,
            sizeof(first_elements) / sizeof(first_elements[0])
        },
        {
            second_elements,
            sizeof(second_elements) / sizeof(second_elements[0])
        }
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    for (size_t i = 0; i < tuple_count; ++i) {
        String *result = NULL;
        size_t result_count = 0;

        if (concatenate_adjacent(&tuples[i],
                                 &result,
                                 &result_count) != 0) {
            fputs("Failed to concatenate tuple elements.\n", stderr);
            return EXIT_FAILURE;
        }

        if (print_string_tuple(result, result_count) != 0) {
            free_string_array(result, result_count);
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }

        free_string_array(result, result_count);
    }

    return EXIT_SUCCESS;
}