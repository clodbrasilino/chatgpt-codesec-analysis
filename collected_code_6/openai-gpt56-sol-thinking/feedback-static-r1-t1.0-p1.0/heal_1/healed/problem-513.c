#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *string)
{
    size_t length;
    char *copy;

    if (string == NULL) {
        return NULL;
    }

    length = strlen(string);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, string, length + 1);
    return copy;
}

static void free_list(const char *const list[], size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free((void *)list[i]);
    }

    free((void *)list);
}

static const char **tuple_to_list(const char *const tuple[],
                                  size_t tuple_count,
                                  const char *string,
                                  size_t *list_count)
{
    const char **list;
    size_t count;
    size_t i;

    if (list_count == NULL || string == NULL ||
        (tuple_count != 0 && tuple == NULL)) {
        return NULL;
    }

    *list_count = 0;

    for (i = 0; i < tuple_count; ++i) {
        if (tuple[i] == NULL) {
            return NULL;
        }
    }

    if (tuple_count > SIZE_MAX / 2) {
        return NULL;
    }

    count = tuple_count * 2;

    if (count == 0) {
        return calloc(1, sizeof(*list));
    }

    if (count > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    list = calloc(count, sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < tuple_count; ++i) {
        list[i * 2] = duplicate_string(tuple[i]);
        if (list[i * 2] == NULL) {
            free_list(list, count);
            return NULL;
        }

        list[i * 2 + 1] = duplicate_string(string);
        if (list[i * 2 + 1] == NULL) {
            free_list(list, count);
            return NULL;
        }
    }

    *list_count = count;
    return list;
}

static int print_list(const char *const list[], size_t count)
{
    size_t i;

    if (count != 0 && list == NULL) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            return -1;
        }

        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputs(list[i], stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *tuple[] = {"alpha", "beta", "gamma"};
    const char *string = "added";
    const char **list;
    size_t list_count;

    list = tuple_to_list(tuple, sizeof(tuple) / sizeof(tuple[0]),
                         string, &list_count);
    if (list == NULL) {
        fputs("Failed to convert tuple to list\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(list, list_count) != 0) {
        free_list(list, list_count);
        return EXIT_FAILURE;
    }

    free_list(list, list_count);
    return EXIT_SUCCESS;
}