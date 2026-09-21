#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0) {
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

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int tuple_to_list(const char *const tuple[],
                         const size_t tuple_sizes[],
                         size_t tuple_count,
                         const char *separator,
                         size_t separator_size,
                         char ***result,
                         size_t *result_count)
{
    char **list;
    size_t count;

    if (result == NULL || result_count == NULL || separator == NULL ||
        separator_size == 0 ||
        (tuple_count != 0 && (tuple == NULL || tuple_sizes == NULL)) ||
        tuple_count > SIZE_MAX / 2) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    count = tuple_count * 2;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*list)) {
        return -1;
    }

    list = calloc(count, sizeof(*list));
    if (list == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuple[i] == NULL || tuple_sizes[i] == 0) {
            free_list(list, count);
            return -1;
        }

        list[i * 2] = duplicate_string(tuple[i], tuple_sizes[i]);
        if (list[i * 2] == NULL) {
            free_list(list, count);
            return -1;
        }

        list[i * 2 + 1] = duplicate_string(separator, separator_size);
        if (list[i * 2 + 1] == NULL) {
            free_list(list, count);
            return -1;
        }
    }

    *result = list;
    *result_count = count;

    return 0;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char separator[] = "added";

    const char *tuple[] = {apple, banana, cherry};
    const size_t tuple_sizes[] = {
        sizeof(apple),
        sizeof(banana),
        sizeof(cherry)
    };

    char **list = NULL;
    size_t list_count = 0;
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);

    if (tuple_to_list(tuple,
                      tuple_sizes,
                      tuple_count,
                      separator,
                      sizeof(separator),
                      &list,
                      &list_count) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (puts(list[i]) == EOF) {
            free_list(list, list_count);
            return EXIT_FAILURE;
        }
    }

    free_list(list, list_count);
    return EXIT_SUCCESS;
}