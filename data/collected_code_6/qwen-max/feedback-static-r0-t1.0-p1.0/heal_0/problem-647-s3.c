#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char** split_at_uppercase(const char *input, int *word_count) {
    *word_count = 0;
    const int max_words = 100;
    char **words = (char **)malloc(max_words * sizeof(char *));
    if (!words) return NULL;

    for (int i = 0; i < max_words; ++i) words[i] = NULL;

    const char *start = input;
    while (*input) {
        if (isupper((unsigned char)*input)) {
            if (input != start) {
                int len = input - start;
                words[*word_count] = (char *)malloc(len * sizeof(char));
                if (!words[*word_count]) {
                    for (int i = 0; i < *word_count; ++i) free(words[i]);
                    free(words);
                    *word_count = 0;
                    return NULL;
                }
                strncpy(words[*word_count], start, len);
                words[*word_count][len] = '\0';
                (*word_count)++;
            }
            start = input;
        }
        ++input;
    }

    if (start != input) {
        int len = input - start;
        words[*word_count] = (char *)malloc(len * sizeof(char));
        if (!words[*word_count]) {
            for (int i = 0; i < *word_count; ++i) free(words[i]);
            free(words);
            *word_count = 0;
            return NULL;
        }
        strncpy(words[*word_count], start, len);
        words[*word_count][len] = '\0';
        (*word_count)++;
    }

    return words;
}

void free_split_words(char **words, int word_count) {
    for (int i = 0; i < word_count; ++i) {
        free(words[i]);
    }
    free(words);
}

int main() {
    const char *input = "HelloWorldExample";
    int word_count;
    char **words = split_at_uppercase(input, &word_count);
    if (words) {
        for (int i = 0; i < word_count; ++i) {
            printf("%s\n", words[i]);
        }
        free_split_words(words, word_count);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    return 0;
}