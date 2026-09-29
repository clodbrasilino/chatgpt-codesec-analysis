#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

static char *duplicate_string(const char *string, size_t length)
{
    char *copy;
    size_t i;

    if (string == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = string[i];
    }

    copy[length] = '\0';
    return copy;
}

static void free_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static char **tuple_to_list(const StringView tuple[], size_t tuple_count,
                            StringView string, size_t *list_count)
{
    char **list;
    size_t count;
    size_t i;

    if (list_count == NULL || string.data == NULL ||
        (tuple_count != 0 && tuple == NULL)) {
        return NULL;
    }

    *list_count = 0;

    for (i = 0; i < tuple_count; ++i) {
        if (tuple[i].data == NULL) {
            return NULL;
        }
    }

    if (tuple_count > SIZE_MAX / 2) {
        return NULL;
    }

    count = tuple_count * 2;

    if (count == 0) {
        return calloc(1, sizeof(char *));
    }

    if (count > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }

    list = calloc(count, sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < tuple_count; ++i) {
        list[i * 2] = duplicate_string(tuple[i].data, tuple[i].length);
        if (list[i * 2] == NULL) {
            free_list(list, count);
            return NULL;
        }

        list[i * 2 + 1] = duplicate_string(string.data, string.length);
        if (list[i * 2 + 1] == NULL) {
            free_list(list, count);
            return NULL;
        }
    }

    *list_count = count;
    return list;
}

static int print_list(char *const *const list, size_t count)
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

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    if (fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";
    static const char gamma[] = "gamma";
    static const char added[] = "added";

    const StringView tuple[] = {
        {alpha, sizeof(alpha) - 1},
        {beta, sizeof(beta) - 1},
        {gamma, sizeof(gamma) - 1}
    };
    const StringView string = {added, sizeof(added) - 1};
    char **list;
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