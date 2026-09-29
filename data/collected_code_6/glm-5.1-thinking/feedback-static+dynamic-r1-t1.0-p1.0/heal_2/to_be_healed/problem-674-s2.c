#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len + 1);

    size_t capacity = 16;
    size_t count = 0;
    char **seen = malloc(capacity * sizeof(char *));
    if (seen == NULL) {
        free(copy);
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        free(copy);
        free(seen);
        return NULL;
    }
    result[0] = '\0';
    size_t offset = 0;

    char *saveptr = NULL;
    char *token = strtok_r(copy, " \t\n", &saveptr);

    while (token != NULL) {
        int found = 0;
        for (size_t i = 0; i < count; i++) {
            if (strcmp(seen[i], token) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (count >= capacity) {
                capacity *= 2;
                char **new_seen = realloc(seen, capacity * sizeof(char *));
                if (new_seen == NULL) {
                    for (size_t i = 0; i < count; i++) free(seen[i]);
                    free(seen);
                    free(copy);
                    free(result);
                    return NULL;
                }
                seen = new_seen;
            }
            seen[count] = strdup(token);
            if (seen[count] == NULL) {
                for (size_t i = 0; i < count; i++) free(seen[i]);
                free(seen);
                free(copy);
                free(result);
                return NULL;
            }
            count++;

            int written;
            if (offset > 0) {
                written = snprintf(result + offset, len + 1 - offset, " %s", token);
            } else {
                written = snprintf(result + offset, len + 1 - offset, "%s", token);
            }
            if (written > 0) {
                size_t written_size = (size_t)written;
                if (written_size < len + 1 - offset) {
                    offset += written_size;
                } else {
                    offset = len;
                }
            }
        }
        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    for (size_t i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(seen);
    free(copy);

    size_t final_len = offset + 1;
    char *final_result = malloc(final_len);
    if (final_result != NULL) {
        snprintf(final_result, final_len, "%s", result);
    }
    free(result);

    return final_result;
}

int main(void) {
    const char *text = "hello world hello this is a test test world";
    char *unique = remove_duplicate_words(text);
    if (unique != NULL) {
        printf("%s\n", unique);
        free(unique);
    }
    return 0;
}