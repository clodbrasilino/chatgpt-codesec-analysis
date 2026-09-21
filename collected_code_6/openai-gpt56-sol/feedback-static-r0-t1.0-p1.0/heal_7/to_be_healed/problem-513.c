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
    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    copy = malloc(length + 1);
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
                         const char *separator,
                         size_t separator_size,
                         char ***result,
                         size_t *result_count)
{
    char **list;
    size_t count;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (separator == NULL || separator_size == 0 ||
        memchr(separator, '\0', separator_size) == NULL) {
        return -1;
    }

    if (tuple_count != 0 && (tuple == NULL || tuple_sizes == NULL)) {
        return -1;
    }

    if (tuple_count > SIZE_MAX / 2) {
        return -1;
    }

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
        size_t index = i * 2;

        if (tuple[i] == NULL || tuple_sizes[i] == 0 ||
            memchr(tuple[i], '\0', tuple_sizes[i]) == NULL) {
            free_list(list, count);
            return -1;
        }

        list[index] = duplicate_string(tuple[i], tuple_sizes[i]);
        if (list[index] == NULL) {
            free_list(list, count);
            return -1;
        }

        list[index + 1] = duplicate_string(separator, separator_size);
        if (list[index + 1] == NULL) {
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

    const char *tuple[] = {
        apple,
        banana,
        cherry
    };

    const size_t tuple_sizes[] = {
        sizeof apple,
        sizeof banana,
        sizeof cherry
    };

    const size_t tuple_count = sizeof tuple / sizeof tuple[0];
    char **list = NULL;
    size_t list_count = 0;

    if (tuple_to_list(tuple,
                      tuple_sizes,
                      tuple_count,
                      separator,
                      sizeof separator,
                      &list,
                      &list_count) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (printf("%s\n", list[i]) < 0) {
            free_list(list, list_count);
            return EXIT_FAILURE;
        }
    }

    free_list(list, list_count);
    return EXIT_SUCCESS;
}