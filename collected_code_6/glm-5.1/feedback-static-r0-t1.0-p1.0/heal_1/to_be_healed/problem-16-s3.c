#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_sequences(const char *str, size_t *count) {
    /* Possible weaknesses found:
     *  Value stored to 'len' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'len' is assigned a value that is never used. [unreadVariable]
     */
    size_t len = strlen(str);
    size_t capacity = 16;
    size_t idx = 0;
    char **results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        *count = 0;
        return NULL;
    }

    const char *p = str;
    while (*p) {
        if (islower((unsigned char)*p)) {
            const char *start = p;
            int valid = 1;
            while (*p && (islower((unsigned char)*p) || *p == '_')) {
                if (*p == '_' && (!p[1] || !islower((unsigned char)p[1]))) {
                    valid = 0;
                    while (*p && (islower((unsigned char)*p) || *p == '_')) {
                        p++;
                    }
                    break;
                }
                p++;
            }
            if (valid && p - start > 1 && start[0] != '_' && p[-1] != '_') {
                size_t match_len = p - start;
                char *match = malloc(match_len + 1);
                if (match == NULL) {
                    for (size_t i = 0; i < idx; i++) {
                        free(results[i]);
                    }
                    free(results);
                    *count = 0;
                    return NULL;
                }
                memcpy(match, start, match_len);
                match[match_len] = '\0';
                if (idx >= capacity) {
                    capacity *= 2;
                    char **new_results = realloc(results, capacity * sizeof(char *));
                    if (new_results == NULL) {
                        free(match);
                        for (size_t i = 0; i < idx; i++) {
                            free(results[i]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    results = new_results;
                }
                results[idx++] = match;
            }
        } else {
            p++;
        }
    }

    char **final_results = realloc(results, (idx + 1) * sizeof(char *));
    if (final_results != NULL) {
        final_results[idx] = NULL;
        results = final_results;
    } else {
        results[idx] = NULL;
    }

    *count = idx;
    return results;
}

int main(void) {
    const char *text = "some valid_snake_case and invalid__double or _leading or trailing_ or mixed_CASE";
    size_t count = 0;
    char **sequences = find_sequences(text, &count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", sequences[i]);
        free(sequences[i]);
    }
    free(sequences);

    return 0;
}