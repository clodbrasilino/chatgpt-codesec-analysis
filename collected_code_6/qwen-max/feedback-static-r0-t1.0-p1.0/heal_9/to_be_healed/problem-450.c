#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_substrings(const char *const *list, size_t list_size, size_t substring_size, size_t *result_count) {
    *result_count = 0;
    if (list == NULL || list_size == 0 || substring_size == 0)
        return NULL;

    char **results = (char **)malloc(list_size * sizeof(char *));
    if (results == NULL)
        return NULL;

    for (size_t i = 0; i < list_size; ++i) {
        const char *str = list[i];
        if (str != NULL) {
            size_t str_len = strnlen(str, substring_size + 1);
            if (str_len >= substring_size) {
                results[*result_count] = (char *)malloc(substring_size + 1);
                if (results[*result_count] == NULL) {
                    for (size_t j = 0; j < *result_count; ++j)
                        free(results[j]);
                    free(results);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(results[*result_count], str, substring_size);
                results[*result_count][substring_size] = '\0';
                (*result_count)++;
            }
        }
    }

    return results;
}

int main() {
    const char *const strings[] = {"hello", "world", "this", "is", "a", "test"};
    size_t list_size = sizeof(strings) / sizeof(strings[0]);
    size_t substring_size = 3;
    size_t result_count;

    char **results = extract_substrings(strings, list_size, substring_size, &result_count);

    if (results != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", results[i]);
            free(results[i]);
        }
        free(results);
    }

    return 0;
}