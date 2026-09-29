#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0U; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static int duplicate_string(const char *source, size_t source_length,
                            char **result)
{
    char *copy;

    if (source == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (source_length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (source_length != 0U) {
        memcpy(copy, source, source_length);
    }
    copy[source_length] = '\0';

    *result = copy;
    return 0;
}

static int tuple_to_list(const char *const tuple[],
                         const size_t tuple_lengths[],
                         size_t tuple_count,
                         const char *added_string,
                         size_t added_string_length,
                         char ***result,
                         size_t *result_count)
{
    char **list;
    size_t list_count;
    size_t initialized = 0U;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0U;

    if (added_string == NULL ||
        (tuple_count != 0U &&
         (tuple == NULL || tuple_lengths == NULL))) {
        return -1;
    }

    if (tuple_count > SIZE_MAX / 2U) {
        return -1;
    }

    list_count = tuple_count * 2U;

    if (list_count == 0U) {
        return 0;
    }

    if (list_count > SIZE_MAX / sizeof(*list)) {
        return -1;
    }

    list = calloc(list_count, sizeof(*list));
    if (list == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        if (tuple[i] == NULL ||
            duplicate_string(tuple[i], tuple_lengths[i],
                             &list[initialized]) != 0) {
            free_list(list, initialized);
            return -1;
        }
        ++initialized;

        if (duplicate_string(added_string, added_string_length,
                             &list[initialized]) != 0) {
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
    const char *const tuple[] = {"one", "two", "three"};
    const size_t tuple_lengths[] = {
        sizeof("one") - 1U,
        sizeof("two") - 1U,
        sizeof("three") - 1U
    };
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    const char added_string[] = "added";
    char **list = NULL;
    size_t list_count = 0U;

    if (tuple_to_list(tuple, tuple_lengths, tuple_count,
                      added_string, sizeof(added_string) - 1U,
                      &list, &list_count) != 0) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < list_count; ++i) {
        if (printf("%s\n", list[i]) < 0) {
            free_list(list, list_count);
            return EXIT_FAILURE;
        }
    }

    free_list(list, list_count);
    return EXIT_SUCCESS;
}