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
    if (results == NULL) {
        *count = 0;
        return NULL;
    }
    *count = 0;

    status = regcomp(&regex, "\\<[a-zA-Z]{5}\\>", REG_EXTENDED);
    if (status != 0) {
        free(results);
        *count = 0;
        return NULL;
    }

    const char *cursor = str;
    while (1) {
        status = regexec(&regex, cursor, 1, &match, 0);
        if (status != 0 || match.rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(results, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            results = temp;
        }

        size_t len = match.rm_eo - match.rm_so;
        /* Possible weaknesses found:
         *  alloc_size is assigned 'len+1' here.
         */
        size_t alloc_size = len + 1;
        /* Possible weaknesses found:
         *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
         *  Condition 'alloc_size<=len' is always false
         */
        if (alloc_size <= len) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        char *word = malloc(alloc_size);
        if (word == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + match.rm_so, alloc_size);

        results[*count] = word;
        (*count)++;

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return results;
}

void free_words(char **words, size_t count) {
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world, this is a regex test finding words like apple and mango.";
    size_t count = 0;
    char **words = find_five_char_words(text, &count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return 0;
}