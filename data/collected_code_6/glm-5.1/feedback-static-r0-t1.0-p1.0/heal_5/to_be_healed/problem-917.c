#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_upper_lower_sequences(const char *str, size_t *out_count) {
    size_t len = 0;
    if (str != NULL) {
        const char *p = str;
        while (*p != '\0') {
            p++;
        }
        len = (size_t)(p - str);
    }

    size_t capacity = 16;
    size_t count = 0;
    char **results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        return NULL;
    }

    if (len == 0) {
        *out_count = 0;
        return results;
    }

    size_t i = 0;
    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            i++;
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
            if (i > start + 1) {
                if (count >= capacity) {
                    capacity *= 2;
                    char **new_results = realloc(results, capacity * sizeof(char *));
                    if (new_results == NULL) {
                        for (size_t j = 0; j < count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        return NULL;
                    }
                    results = new_results;
                }
                size_t seq_len = i - start;
                char *seq = malloc(seq_len + 1);
                if (seq == NULL) {
                    for (size_t j = 0; j < count; j++) {
                        free(results[j]);
                    }
                    free(results);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(seq, str + start, seq_len);
                seq[seq_len] = '\0';
                results[count] = seq;
                count++;
            }
        } else {
            i++;
        }
    }

    *out_count = count;
    return results;
}

int main(void) {
    const char *text = "The QuickBrown Fox Jumped Over The Lazy Dog and A bb Cs D";
    size_t count = 0;
    char **sequences = find_upper_lower_sequences(text, &count);

    if (sequences != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", sequences[i]);
            free(sequences[i]);
        }
        free(sequences);
    }

    return 0;
}