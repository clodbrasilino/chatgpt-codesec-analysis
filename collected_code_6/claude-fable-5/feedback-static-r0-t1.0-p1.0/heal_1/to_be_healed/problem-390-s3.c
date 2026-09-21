#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **prepend_to_all(const char *prefix, const char *const *items, size_t count)
{
    char **result;
    size_t i;
    size_t prefix_len;

    if (prefix == NULL || items == NULL) {
        return NULL;
    }

    result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_len = strlen(prefix);

    for (i = 0; i < count; i++) {
        size_t item_len;
        size_t total_len;

        if (items[i] == NULL) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        item_len = strlen(items[i]);
        total_len = prefix_len + item_len + 1U;

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + prefix_len, items[i], item_len + 1U);
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