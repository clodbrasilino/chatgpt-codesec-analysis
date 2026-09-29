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
    size_t allocation_size;
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

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int tuple_to_list(const char *const tuple[],
                         const size_t tuple_sizes[],
                         size_t tuple_count,
                         const char *added_string,
                         size_t added_string_size,
                         char ***result,
                         size_t *result_count)
{
    char **list;
    size_t list_count;
    size_t initialized = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (added_string == NULL ||
        added_string_size == 0 ||
        memchr(added_string, '\0', added_string_size) == NULL) {
        return -1;
    }

    if (tuple_count == 0) {
        return 0;
    }

    if (tuple == NULL || tuple_sizes == NULL) {
        return -1;
    }

    if (tuple_count > SIZE_MAX / 2) {
        return -1;
    }

    list_count = tuple_count * 2;

    if (list_count > SIZE_MAX / sizeof(*list)) {
        return -1;
    }

    list = calloc(list_count, sizeof(*list));
    if (list == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuple[i] == NULL ||
            tuple_sizes[i] == 0 ||
            memchr(tuple[i], '\0', tuple_sizes[i]) == NULL) {
            free_list(list, initialized);
            return -1;
        }

        list[initialized] = duplicate_string(tuple[i], tuple_sizes[i]);
        if (list[initialized] == NULL) {
            free_list(list, initialized);
            return -1;
        }
        ++initialized;

        list[initialized] =
            duplicate_string(added_string, added_string_size);
        if (list[initialized] == NULL) {
            free_list(list, initialized);
            return -1;
        }
        ++initialized;
    }

    *result = list;
    *result_count = list_count;
    return 0;
}

int main(void)
{
    static const char item_one[] = "one";
    static const char item_two[] = "two";
    static const char item_three[] = "three";
    static const char added_string[] = "added";

    const char *const tuple[] = {
        item_one,
        item_two,
        item_three
    };

    const size_t tuple_sizes[] = {
        sizeof(item_one),
        sizeof(item_two),
        sizeof(item_three)
    };

    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    char **list = NULL;
    size_t list_count = 0;

    if (tuple_to_list(tuple,
                      tuple_sizes,
                      tuple_count,
                      added_string,
                      sizeof(added_string),
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