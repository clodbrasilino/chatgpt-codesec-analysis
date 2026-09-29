#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096

static void cleanup_partial(char **list, size_t filled)
{
    while (filled > 0) {
        filled--;
        free(list[filled]);
    }
    free(list);
}

char **prepend_to_all(const char *prefix, const char **items, size_t count)
{
    char **result;
    size_t i;
    size_t prefix_len;

    if (prefix == NULL || items == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    prefix_len = strnlen(prefix, MAX_STRING_LEN);
    if (prefix_len >= MAX_STRING_LEN) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t item_len;
        size_t total_len;

        if (items[i] == NULL) {
            cleanup_partial(result, i);
            return NULL;
        }

        item_len = strnlen(items[i], MAX_STRING_LEN);
        if (item_len >= MAX_STRING_LEN) {
            cleanup_partial(result, i);
            return NULL;
        }

        if (prefix_len > SIZE_MAX - item_len - 1) {
            cleanup_partial(result, i);
            return NULL;
        }

        total_len = prefix_len + item_len + 1;

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            cleanup_partial(result, i);
            return NULL;
        }

        if (prefix_len > total_len || item_len > total_len - prefix_len) {
            free(result[i]);
            cleanup_partial(result, i);
            return NULL;
        }

        memcpy(result[i], prefix, prefix_len);
        memcpy(result[i] + prefix_len, items[i], item_len);
        result[i][total_len - 1] = '\0';
    }

    return result;
}

void free_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    const char *items[] = { "apple", "banana", "cherry" };
    size_t count = sizeof(items) / sizeof(items[0]);
    char **result;
    size_t i;

    result = prepend_to_all("fruit_", items, count);
    if (result == NULL) {
        fprintf(stderr, "Failed to build list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", result[i]) < 0) {
            free_list(result, count);
            return EXIT_FAILURE;
        }
    }

    free_list(result, count);
    return EXIT_SUCCESS;
}