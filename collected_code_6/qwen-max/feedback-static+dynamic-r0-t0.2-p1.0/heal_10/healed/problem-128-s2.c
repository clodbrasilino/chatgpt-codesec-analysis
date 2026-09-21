#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_long_words(const char *words[], int word_count, int n, int *filtered_count) {
    *filtered_count = 0;
    for (int i = 0; i < word_count; ++i) {
        if (words[i] && strnlen(words[i], 1024) > n) {
            (*filtered_count)++;
        }
    }

    char **result = (char **)malloc(*filtered_count * sizeof(char *));
    if (result == NULL) return NULL;

    int index = 0;
    for (int i = 0; i < word_count; ++i) {
        if (words[i] && strnlen(words[i], 1024) > n) {
            size_t len = strnlen(words[i], 1024);
            result[index] = (char *)malloc((len + 1) * sizeof(char));
            if (result[index] == NULL) {
                while (index > 0) {
                    free(result[--index]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[index], words[i], len);
            result[index][len] = '\0';
            index++;
        }
    }

    return result;
}

int main() {
    const char *words[] = {"hello", "world", "a", "of", "programming"};
    int word_count = 5;
    int n = 3;
    int filtered_count;

    char **filtered_words = filter_long_words(words, word_count, n, &filtered_count);

    if (filtered_words != NULL) {
        for (int i = 0; i < filtered_count; ++i) {
            printf("%s\n", filtered_words[i]);
            free(filtered_words[i]);
        }
        free(filtered_words);
    }

    return 0;
}