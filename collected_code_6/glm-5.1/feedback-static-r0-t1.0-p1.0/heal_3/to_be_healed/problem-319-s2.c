#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_five_char_words(const char *str, size_t *count) {
    regex_t regex;
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
    /* Possible weaknesses found:
     *  Although the value stored to 'status' is used in the enclosing expression, the value is never actually read from 'status' [deadcode.DeadStores]
     */
    while ((status = regexec(&regex, cursor, 1, &(regmatch_t){0}, 0)) == 0) {
        regmatch_t match;
        regexec(&regex, cursor, 1, &match, 0);
        
        if (match.rm_so == -1) {
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
        char *word = malloc(len + 1);
        if (word == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        memcpy(word, cursor + match.rm_so, len);
        word[len] = '\0';
        results[*count] = word;
        (*count)++;

        cursor += match.rm_eo;
    }

    if (*count == 0) {
        free(results);
        results = NULL;
    } else {
        char **shrunk = realloc(results, *count * sizeof(char *));
        if (shrunk != NULL) {
            results = shrunk;
        }
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