#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **concat_elements(const char **tuple, int tuple_size, const char *delimiter, int *result_count) {
    if (tuple == NULL || delimiter == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    if (tuple_size <= 1) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < tuple_size; i++) {
        if (tuple[i] == NULL) {
            *result_count = 0;
            return NULL;
        }
    }

    if (delimiter[0] == '\0') {
        *result_count = 0;
        return NULL;
    }

    char **result = (char **)malloc((tuple_size - 1) * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t delim_len = strlen(delimiter);
    int count = 0;

    for (int i = 0; i < tuple_size - 1; i++) {
        size_t len1 = strlen(tuple[i]);
        size_t len2 = strlen(tuple[i + 1]);
        size_t total_len = len1 + delim_len + len2;

        if (total_len < len1 || total_len < len2) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }

        char *combined = (char *)malloc(total_len + 1);
        if (combined == NULL) {
            for (int j = 0; j < count; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }

        memcpy(combined, tuple[i], len1);
        memcpy(combined + len1, delimiter, delim_len);
        memcpy(combined + len1 + delim_len, tuple[i + 1], len2);
        combined[total_len] = '\0';
        result[count++] = combined;
    }

    *result_count = count;
    return result;
}

int main(void) {
    const char *tuple[] = {"hello", "world", "foo", "bar"};
    int result_count = 0;
    char **result = concat_elements(tuple, 4, "-", &result_count);

    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate elements\n");
        return 1;
    }

    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}