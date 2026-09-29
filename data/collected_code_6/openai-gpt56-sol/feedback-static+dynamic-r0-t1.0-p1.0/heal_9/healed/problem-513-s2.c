#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *duplicate_string(const char *source, size_t source_length)
{
    if (source == NULL || source_length == SIZE_MAX) {
        return NULL;
    }

    if (memchr(source, '\0', source_length) != NULL) {
        return NULL;
    }

    size_t allocation_size = source_length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return NULL;
    }

    if (source_length > 0) {
        memcpy(copy, source, source_length);
    }

    copy[source_length] = '\0';
    return copy;
}

static int tuple_to_list(const char *const tuple[],
                         const size_t tuple_lengths[],
                         size_t tuple_count,
                         const char *separator,
                         size_t separator_length,
                         char ***result,
                         size_t *result_count)
{
    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple == NULL || tuple_lengths == NULL || separator == NULL) {
        return -1;
    }

    if (separator_length == SIZE_MAX ||
        tuple_count > SIZE_MAX / 2) {
        return -1;
    }

    size_t count = tuple_count * 2;

    if (count > SIZE_MAX / sizeof(char *)) {
        return -1;
    }

    char **list = calloc(count, sizeof(*list));

    if (list == NULL) {
        return -1;
    }

    size_t initialized_count = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuple[i] == NULL || tuple_lengths[i] == SIZE_MAX) {
            free_string_list(list, initialized_count);
            return -1;
        }

        char *value = duplicate_string(tuple[i], tuple_lengths[i]);

        if (value == NULL) {
            free_string_list(list, initialized_count);
            return -1;
        }

        list[initialized_count++] = value;

        char *separator_copy = duplicate_string(separator, separator_length);

        if (separator_copy == NULL) {
            free_string_list(list, initialized_count);
            return -1;
        }

        list[initialized_count++] = separator_copy;
    }

    *result = list;
    *result_count = initialized_count;
    return 0;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char separator[] = "after";

    const char *tuple[] = {
        apple,
        banana,
        cherry
    };

    const size_t tuple_lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1
    };

    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    char **list = NULL;
    size_t list_count = 0;

    if (tuple_to_list(tuple,
                      tuple_lengths,
                      tuple_count,
                      separator,
                      sizeof(separator) - 1,
                      &list,
                      &list_count) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (puts(list[i]) == EOF) {
            free_string_list(list, list_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(list, list_count);
    return EXIT_SUCCESS;
}