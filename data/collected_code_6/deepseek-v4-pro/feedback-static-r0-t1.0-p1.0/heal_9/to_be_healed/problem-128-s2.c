#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char **shortlist_long_words(const char *words[], int word_count, size_t n, int *out_count) {
    char **result = NULL;
    int count = 0;

    if (words == NULL || out_count == NULL || word_count <= 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    result = malloc((size_t)word_count * sizeof(char *));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL) {
            size_t len = safe_strlen(words[i], n + 1);
            if (len > n) {
                size_t full_len = safe_strlen(words[i], SIZE_MAX);
                
                if (full_len == SIZE_MAX) {
                    for (int j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }

                if (full_len >= SIZE_MAX - 1) {
                    for (int j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }

                size_t alloc_size = full_len + 1;

                result[count] = malloc(alloc_size);
                if (result[count] == NULL) {
                    for (int j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[count], words[i], full_len);
                result[count][full_len] = '\0';
                count++;
            }
        }
    }

    if (count == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    char **shrunk = realloc(result, (size_t)count * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    }

    *out_count = count;
    return result;
}

int main(void) {
    const char *words[] = {"apple", "banana", "kiwi", "strawberry", "plum", "watermelon"};
    int word_count = (int)(sizeof(words) / sizeof(words[0]));
    size_t n = 5;
    int shortlisted_count = 0;

    char **shortlisted = shortlist_long_words(words, word_count, n, &shortlisted_count);

    if (shortlisted == NULL || shortlisted_count == 0) {
        printf("No words longer than %zu characters found.\n", n);
        return 0;
    }

    printf("Words longer than %zu characters:\n", n);
    for (int i = 0; i < shortlisted_count; i++) {
        printf("%s\n", shortlisted[i]);
        free(shortlisted[i]);
    }

    free(shortlisted);
    return 0;
}