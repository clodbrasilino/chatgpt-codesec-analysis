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

    regmatch_t pmatch[1];
    const char *p = text;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        if (*out_count >= capacity) {
            capacity *= 2;
            char **new_words = realloc(words, capacity * sizeof(char *));
            if (!new_words) {
                free_words(words, *out_count);
                regfree(&regex);
                return NULL;
            }
            words = new_words;
        }

        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        words[*out_count] = malloc(len + 1);
        if (words[*out_count]) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[*out_count], p + pmatch[0].rm_so, len);
            words[*out_count][len] = '\0';
            (*out_count)++;
        }

        p += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return words;
}

void free_words(char **words, size_t count) {
    if (!words) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *sample_text = "This is a simple text with some longer words.";
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