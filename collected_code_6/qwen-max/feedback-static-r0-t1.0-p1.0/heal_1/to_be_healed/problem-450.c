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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i] != NULL && strlen(list[i]) >= substring_size) {
            results[*result_count] = (char *)malloc(substring_size + 1);
            if (results[*result_count] == NULL) {
                while (*result_count > 0) {
                    free(results[--(*result_count)]);
                }
                free(results);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(results[*result_count], list[i], substring_size);
            results[*result_count][substring_size] = '\0';
            (*result_count)++;
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