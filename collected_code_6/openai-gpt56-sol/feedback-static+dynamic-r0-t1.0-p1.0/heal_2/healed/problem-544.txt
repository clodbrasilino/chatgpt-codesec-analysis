#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

static int checked_add(size_t a, size_t b, size_t *result)
{
    if (result == NULL || a > SIZE_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_multiply(size_t a, size_t b, size_t *result)
{
    if (result == NULL || (a != 0 && b > SIZE_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int bounded_string_length(const char *string, size_t limit,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL || limit == 0) {
        return 0;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

static int copy_bytes(char *destination, size_t capacity, size_t *offset,
                      const char *source, size_t length)
{
    if (destination == NULL || offset == NULL || source == NULL ||
        *offset > capacity || length > capacity - *offset) {
        return 0;
    }

    if (length != 0) {
        memcpy(destination + *offset, source, length);
    }

    *offset += length;
    return 1;
}

static int append_character(char *destination, size_t capacity, size_t *offset,
                            char character)
{
    if (destination == NULL || offset == NULL || *offset >= capacity) {
        return 0;
    }

    destination[(*offset)++] = character;
    return 1;
}

static char *flatten_tuple_list(const Tuple *tuples, size_t count)
{
    const size_t maximum_string_length = 4096;
    size_t length_count;
    size_t lengths_size;
    size_t *lengths = NULL;
    size_t total_length = 0;
    size_t allocation_size;
    size_t offset = 0;
    char *result = NULL;

    if (count != 0 && tuples == NULL) {
        return NULL;
    }

    if (!checked_multiply(count, 2, &length_count) ||
        !checked_multiply(length_count, sizeof(*lengths), &lengths_size)) {
        return NULL;
    }

    if (lengths_size != 0) {
        lengths = malloc(lengths_size);
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t first_length;
        size_t second_length;

        if (!bounded_string_length(tuples[i].first,
                                   maximum_string_length + 1,
                                   &first_length) ||
            !bounded_string_length(tuples[i].second,
                                   maximum_string_length + 1,
                                   &second_length)) {
            free(lengths);
            return NULL;
        }

        lengths[2 * i] = first_length;
        lengths[2 * i + 1] = second_length;

        if (!checked_add(total_length, first_length, &total_length) ||
            !checked_add(total_length, 1, &total_length) ||
            !checked_add(total_length, second_length, &total_length) ||
            (i + 1 < count &&
             !checked_add(total_length, 1, &total_length))) {
            free(lengths);
            return NULL;
        }
    }

    if (!checked_add(total_length, 1, &allocation_size)) {
        free(lengths);
        return NULL;
    }

    result = malloc(allocation_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t first_length = lengths[2 * i];
        size_t second_length = lengths[2 * i + 1];

        if (!copy_bytes(result, total_length, &offset,
                        tuples[i].first, first_length) ||
            !append_character(result, total_length, &offset, ',') ||
            !copy_bytes(result, total_length, &offset,
                        tuples[i].second, second_length) ||
            (i + 1 < count &&
             !append_character(result, total_length, &offset, ' '))) {
            free(result);
            free(lengths);
            return NULL;
        }
    }

    if (offset != total_length || offset >= allocation_size) {
        free(result);
        free(lengths);
        return NULL;
    }

    result[offset] = '\0';
    free(lengths);
    return result;
}

int main(void)
{
    const Tuple tuples[] = {
        {"apple", "red"},
        {"banana", "yellow"},
        {"grape", "purple"}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    char *flattened = flatten_tuple_list(tuples, count);

    if (flattened == NULL) {
        fputs("Failed to flatten tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}