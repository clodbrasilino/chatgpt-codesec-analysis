#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_words(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int status;
    size_t capacity = 10;
    size_t num_words = 0;
    char **words = malloc(capacity * sizeof(char *));

    if (!words) {
        *count = 0;
        return NULL;
    }

    status = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (status != 0) {
        free(words);
        *count = 0;
        return NULL;
    }

    const char *p = str;
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }

        if (num_words >= capacity) {
            capacity *= 2;
            char **temp = realloc(words, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < num_words; i++) {
                    free(words[i]);
                }
                free(words);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            words = temp;
        }

        size_t len = match.rm_eo - match.rm_so;
        char *word = malloc(len + 1);
        if (!word) {
            for (size_t i = 0; i < num_words; i++) {
                free(words[i]);
            }
            free(words);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        memcpy(word, p + match.rm_so, len);
        word[len] = '\0';
        words[num_words++] = word;

        p += match.rm_eo;
    }

    regfree(&regex);

    char **final_words = realloc(words, num_words * sizeof(char *));
    if (final_words) {
        words = final_words;
    }

    *count = num_words;
    return words;
}

void free_words(char **words, size_t count) {
    if (words) {
        for (size_t i = 0; i < count; i++) {
            free(words[i]);
        }
        free(words);
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog and programming";
    size_t count = 0;

    char **words = find_words(text, &count);
    if (words) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        free_words(words, count);
    }

    return 0;
}