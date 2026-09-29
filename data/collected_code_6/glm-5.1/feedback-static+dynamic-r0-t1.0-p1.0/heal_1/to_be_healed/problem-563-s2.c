#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_quoted(const char *str, size_t *count) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Variable 'len' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'len' during its initialization is never read [deadcode.DeadStores]
     */
    size_t len = strlen(str);
    size_t capacity = 10;
    size_t idx = 0;
    char **results = malloc(capacity * sizeof(char *));
    if (!results) {
        return NULL;
    }

    const char *p = str;
    while (*p) {
        const char *start = strchr(p, '"');
        if (!start) {
            break;
        }
        const char *end = strchr(start + 1, '"');
        if (!end) {
            break;
        }

        size_t substr_len = end - (start + 1);
        char *substr = malloc(substr_len + 1);
        if (!substr) {
            for (size_t i = 0; i < idx; i++) {
                free(results[i]);
            }
            free(results);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(substr, start + 1, substr_len);
        substr[substr_len] = '\0';

        if (idx >= capacity) {
            size_t new_capacity = capacity * 2;
            char **temp = realloc(results, new_capacity * sizeof(char *));
            if (!temp) {
                free(substr);
                for (size_t i = 0; i < idx; i++) {
                    free(results[i]);
                }
                free(results);
                return NULL;
            }
            results = temp;
            capacity = new_capacity;
        }

        results[idx++] = substr;
        p = end + 1;
    }

    char **final_results = realloc(results, (idx + 1) * sizeof(char *));
    if (!final_results) {
        for (size_t i = 0; i < idx; i++) {
            free(results[i]);
        }
        free(results);
        return NULL;
    }
    final_results[idx] = NULL;
    *count = idx;

    return final_results;
}

void free_extracted(char **results) {
    if (!results) {
        return;
    }
    for (size_t i = 0; results[i] != NULL; i++) {
        free(results[i]);
    }
    free(results);
}

int main(void) {
    const char *text = "Extract \"this value\" and \"that value\" from the string";
    size_t count = 0;
    char **values = extract_quoted(text, &count);

    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
        }
        free_extracted(values);
    }

    return 0;
}