#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LEN 8192

char **shortlist_words(const char *const *words, size_t num_words, size_t n, size_t *out_count) {
    if (!words || !out_count) {
        return NULL;
    }

    size_t capacity = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (words[i]) {
            size_t len = 0;
            while (words[i][len] != '\0' && len <= n) {
                len++;
            }
            if (len > n) {
                capacity++;
            }
        }
    }

    *out_count = 0;
    if (capacity == 0) {
        return NULL;
    }

    char **result = malloc(capacity * sizeof(char *));
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < num_words; i++) {
        if (words[i]) {
            size_t len = 0;
            while (words[i][len] != '\0' && len < MAX_WORD_LEN) {
                len++;
            }
            
            if (len > n) {
                result[*out_count] = malloc(len + 1);
                if (!result[*out_count]) {
                    for (size_t j = 0; j < *out_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }
                
                for (size_t j = 0; j < len; j++) {
                    result[*out_count][j] = words[i][j];
                }
                result[*out_count][len] = '\0';
                (*out_count)++;
            }
        }
    }

    return result;
}

int main(void) {
    const char *const dictionary[] = {
        "apple", "cat", "banana", "dog", "elephant", "fox"
    };
    size_t num_words = sizeof(dictionary) / sizeof(dictionary[0]);
    size_t n = 4;
    size_t out_count = 0;

    char **shortlisted = shortlist_words(dictionary, num_words, n, &out_count);

    if (shortlisted) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", shortlisted[i]);
            free(shortlisted[i]);
        }
        free(shortlisted);
    }

    return 0;
}