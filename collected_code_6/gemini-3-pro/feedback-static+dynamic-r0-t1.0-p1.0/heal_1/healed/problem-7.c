#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_words_min_length_4(const char *text, size_t *out_count);
void free_words(char **words, size_t count);

char **find_words_min_length_4(const char *text, size_t *out_count) {
    if (!text || !out_count) {
        return NULL;
    }

    *out_count = 0;
    regex_t regex;
    
    if (regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 10;
    char **words = malloc(capacity * sizeof(char *));
    if (!words) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    const char *cursor = text;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len = match.rm_eo - match.rm_so;
        char *word = malloc(len + 1);
        if (word) {
            strncpy(word, cursor + match.rm_so, len);
            word[len] = '\0';

            if (*out_count >= capacity) {
                capacity *= 2;
                char **temp = realloc(words, capacity * sizeof(char *));
                if (!temp) {
                    free(word);
                    break;
                }
                words = temp;
            }
            words[*out_count] = word;
            (*out_count)++;
        }
        cursor += match.rm_eo;
    }

    regfree(&regex);
    return words;
}

void free_words(char **words, size_t count) {
    if (!words) return;
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *sample_text = "This is a simple text containing some longer words like elephant and programming.";
    size_t count = 0;
    
    char **words = find_words_min_length_4(sample_text, &count);
    
    if (words) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, count);
    }
    
    return 0;
}