#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_five_char_words(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int status;
    size_t capacity = 10;
    char **results = malloc(capacity * sizeof(char *));
    if (!results) {
        return NULL;
    }
    *count = 0;

    status = regcomp(&regex, "\\<[a-zA-Z]{5}\\>", REG_EXTENDED);
    if (status != 0) {
        free(results);
        return NULL;
    }

    const char *p = str;
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(results, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            results = temp;
        }

        size_t len = match.rm_eo - match.rm_so;
        char *word = malloc(len + 1);
        if (!word) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            return NULL;
        }

        memcpy(word, p + match.rm_so, len);
        word[len] = '\0';

        results[*count] = word;
        (*count)++;

        p += match.rm_eo;
    }

    regfree(&regex);
    return results;
}

int main(void) {
    const char *text = "Hello world this is a test string with apple and grace";
    size_t count = 0;
    char **words = find_five_char_words(text, &count);

    if (words) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
        free(words);
    }

    return 0;
}