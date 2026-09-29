#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **prepend_to_all(const char *prefix, const char **items, size_t count)
{
    char **result;
    size_t i;
    size_t prefix_len;

    if (prefix == NULL || items == NULL) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
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
            while (i > 0) {
                i--;
                free(result[i]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        item_len = strlen(items[i]);
        total_len = prefix_len + item_len + 1;

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            while (i > 0) {
                i--;
                free(result[i]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + prefix_len, items[i], item_len);
        result[i][prefix_len + item_len] = '\0';
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