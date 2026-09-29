#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool contains_substring(const char *str, const char *substring) {
    return strstr(str, substring) != NULL;
}

char **remove_words_with_char(char **words, int word_count, const char *substring, int *new_word_count) {
    int count = 0;
    for (int i = 0; i < word_count; ++i) {
        if (!contains_substring(words[i], substring)) {
            count++;
        }
    }

    char **filtered_words = (char **)malloc(sizeof(char *) * count);
    if (filtered_words == NULL) {
        *new_word_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < word_count; ++i) {
        if (!contains_substring(words[i], substring)) {
            filtered_words[index++] = words[i];
        }
    }

    *new_word_count = count;
    return filtered_words;
}

int main() {
    char *words[] = {"hello", "world", "test", "sample", "lorem", "ipsum"};
    int word_count = 6;
    const char *substring = "o";

    int new_word_count;
    char **filtered_words = remove_words_with_char(words, word_count, substring, &new_word_count);

    for (int i = 0; i < new_word_count; ++i) {
        printf("%s\n", filtered_words[i]);
    }

    free(filtered_words);
    return 0;
}