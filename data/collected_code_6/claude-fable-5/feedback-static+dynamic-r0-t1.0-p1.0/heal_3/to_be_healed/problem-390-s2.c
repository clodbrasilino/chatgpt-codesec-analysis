#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static void free_partial(char **list, size_t count)
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

    result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    prefix_len = strnlen(prefix, MAX_STR_LEN);
    if (prefix_len == MAX_STR_LEN && prefix[MAX_STR_LEN - 1] != '\0') {
        free(result);
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t item_len;
        size_t total_len;

        if (items[i] == NULL) {
            free_partial(result, i);
            return NULL;
        }

        item_len = strnlen(items[i], MAX_STR_LEN);
        if (item_len == MAX_STR_LEN && items[i][MAX_STR_LEN - 1] != '\0') {
            free_partial(result, i);
            return NULL;
        }

        if (item_len > SIZE_MAX - 1 || prefix_len > SIZE_MAX - item_len - 1) {
            free_partial(result, i);
            return NULL;
        }

        total_len = prefix_len + item_len + 1;

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            free_partial(result, i);
            return NULL;
        }

        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i], prefix, prefix_len);
        }
        if (item_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i] + prefix_len, items[i], item_len);
        }
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