#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *str, size_t str_len) {
    if (str == NULL) {
        return NULL;
    }

    char *copy = malloc(str_len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, str_len);
    copy[str_len] = '\0';

    size_t capacity = str_len + 1;
    char *result = malloc(capacity);
    if (result == NULL) {
        free(copy);
        return NULL;
    }

    size_t len = 0;
    result[0] = '\0';

    size_t seen_capacity = 16;
    size_t seen_count = 0;
    char **seen = malloc(seen_capacity * sizeof(char *));
    if (seen == NULL) {
        free(copy);
        free(result);
        return NULL;
    }

    char *saveptr = NULL;
    const char *delim = " \t\n";
    char *token = strtok_r(copy, delim, &saveptr);

    while (token != NULL) {
        int is_duplicate = 0;
        for (size_t i = 0; i < seen_count; i++) {
            if (strcmp(seen[i], token) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            if (seen_count == seen_capacity) {
                seen_capacity *= 2;
                char **new_seen = realloc(seen, seen_capacity * sizeof(char *));
                if (new_seen == NULL) {
                    for (size_t i = 0; i < seen_count; i++) free(seen[i]);
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                seen = new_seen;
            }

            char *key = strdup(token);
            if (key != NULL) {
                seen[seen_count++] = key;
                int written;
                if (len > 0) {
                    written = snprintf(result + len, capacity - len, " %s", token);
                } else {
                    written = snprintf(result + len, capacity - len, "%s", token);
                }
                if (written > 0) {
                    if ((size_t)written >= capacity - len) {
                        len = capacity - 1;
                    } else {
                        len += written;
                    }
                }
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    for (size_t i = 0; i < seen_count; i++) {
        free(seen[i]);
    }
    free(seen);
    free(copy);

    char *final_result = realloc(result, len + 1);
    if (final_result == NULL) {
        return result;
    }

    return final_result;
}

int main(void) {
    const char *text = "hello world hello this is a test test world";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *unique = remove_duplicate_words(text, strlen(text));
    if (unique != NULL) {
        printf("%s\n", unique);
        free(unique);
    }
    return 0;
}