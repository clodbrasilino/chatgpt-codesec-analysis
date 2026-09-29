#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096U

char **prepend_to_all(const char *prefix, const char *const *items, size_t count);
void free_string_list(char **list, size_t count);

char **prepend_to_all(const char *prefix, const char *const *items, size_t count)
{
    char **result;
    size_t i;
    size_t prefix_len;

    if (prefix == NULL || items == NULL || count == 0U) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    prefix_len = strnlen(prefix, MAX_STR_LEN);
    if (prefix_len >= MAX_STR_LEN) {
        return NULL;
    }

    result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t item_len;
        size_t total_len;

        if (items[i] == NULL) {
            goto cleanup;
        }

        item_len = strnlen(items[i], MAX_STR_LEN);
        if (item_len >= MAX_STR_LEN) {
            goto cleanup;
        }

        if (item_len > SIZE_MAX - 1U || prefix_len > SIZE_MAX - item_len - 1U) {
            goto cleanup;
        }

        total_len = prefix_len + item_len + 1U;

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            goto cleanup;
        }

        memcpy(result[i], prefix, prefix_len);
        memcpy(result[i] + prefix_len, items[i], item_len);
        result[i][prefix_len + item_len] = '\0';
    }

    return result;

cleanup:
    for (i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
    return NULL;
}

void free_string_list(char **list, size_t count)
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
    const char *const items[] = { "apple", "banana", "cherry" };
    const size_t count = sizeof(items) / sizeof(items[0]);
    const char *prefix = "fruit_";
    char **result;
    size_t i;

    result = prepend_to_all(prefix, items, count);
    if (result == NULL) {
        fprintf(stderr, "Failed to build prefixed list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s\n", result[i]) < 0) {
            free_string_list(result, count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(result, count);
    return EXIT_SUCCESS;
}