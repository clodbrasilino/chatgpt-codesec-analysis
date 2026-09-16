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
        if (list[i] != NULL && strlen(list[i]) >= substring_size) {
            results[*result_count] = (char *)malloc(substring_size + 1);
            if (results[*result_count] == NULL) {
                while (*result_count > 0) {
                    free(results[--(*result_count)]);
                }
                free(results);
                return NULL;
            }
            strncpy(results[*result_count], list[i], substring_size);
            results[*result_count][substring_size] = '\0';
            if (strlen(list[i]) == substring_size) {
                results[*result_count][substring_size] = '\0';
            } else {
                results[*result_count][substring_size] = '\0';
            }
            (*result_count)++;
        }
    }

    return results;
}

int main() {
    const char *const strings[] = {"practice", "solution", "exercises", "Python"};
    size_t list_size = sizeof(strings) / sizeof(strings[0]);
    size_t substring_size_0 = 9;
    size_t substring_size_1 = 6;
    size_t substring_size_2 = 6;
    size_t result_count;

    char **results_0 = extract_substrings(strings, list_size, substring_size_0, &result_count);
    if (results_0 != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", results_0[i]);
            free(results_0[i]);
        }
        free(results_0);
    }

    result_count = 0;
    char **results_1 = extract_substrings(strings, list_size, substring_size_1, &result_count);
    if (results_1 != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", results_1[i]);
            free(results_1[i]);
        }
        free(results_1);
    }

    result_count = 0;
    char **results_2 = extract_substrings(strings, list_size, substring_size_2, &result_count);
    if (results_2 != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", results_2[i]);
            free(results_2[i]);
        }
        free(results_2);
    }

    return 0;
}