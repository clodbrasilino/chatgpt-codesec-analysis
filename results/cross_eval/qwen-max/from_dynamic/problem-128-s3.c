#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **filter_words(char *words[], int word_count, int n, int *filtered_count) {
    if (!words || word_count <= 0 || n < 0) return NULL;
    *filtered_count = 0;
    for (int i = 0; i < word_count; i++) {
        if (strlen(words[i]) > n) (*filtered_count)++;
    }
    char **filtered_words = (char **)malloc(*filtered_count * sizeof(char *));
    if (!filtered_words) return NULL;
    int j = 0;
    for (int i = 0; i < word_count; i++) {
        if (strlen(words[i]) > n) {
            filtered_words[j] = strdup(words[i]);
            if (!filtered_words[j++]) {
                while (j > 0) free(filtered_words[--j]);
                free(filtered_words);
                return NULL;
            }
        }
    }
    return filtered_words;
}

static void free_filtered_words(char **filtered_words, int count) {
    for (int i = 0; i < count; i++) {
        free(filtered_words[i]);
    }
    free(filtered_words);
}

int main() {
    char *words[] = {"hello", "world", "abc", "code", "C", "programming"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int n = 3;

    int filtered_count;
    char **filtered_words = filter_words(words, word_count, n, &filtered_count);

    if (filtered_words) {
        for (int i = 0; i < filtered_count; i++) {
            printf("%s\n", filtered_words[i]);
        }
        free_filtered_words(filtered_words, filtered_count);
    }

    return 0;
}