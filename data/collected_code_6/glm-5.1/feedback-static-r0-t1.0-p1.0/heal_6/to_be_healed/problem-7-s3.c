#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

char **find_words(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    char **result = NULL;
    size_t capacity = 0;
    *count = 0;

    ret = regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    const char *cursor = str;
    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH || match.rm_so == -1 || match.rm_eo == -1) {
            break;
        }

        size_t word_len = match.rm_eo - match.rm_so;
        if (*count >= capacity) {
            size_t new_capacity = capacity == 0 ? 10 : capacity * 2;
            char **new_result = realloc(result, new_capacity * sizeof(char *));
            if (!new_result) {
                regfree(&regex);
                for (size_t i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            result = new_result;
            capacity = new_capacity;
        }

        if (word_len == 0) {
            cursor += match.rm_eo + 1;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (cursor > str + strlen(str)) {
                break;
            }
            continue;
        }

        char *word = malloc(word_len + 1);
        if (!word) {
            regfree(&regex);
            for (size_t i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + match.rm_so, word_len);
        word[word_len] = '\0';
        result[*count] = word;
        (*count)++;

        cursor += match.rm_eo;
    }

    regfree(&regex);

    if (*count > 0) {
        char **final_result = realloc(result, *count * sizeof(char *));
        if (final_result) {
            result = final_result;
        }
    } else {
        free(result);
        result = NULL;
    }

    return result;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t count = 0;
    char **words = find_words(argv[1], &count);

    if (words) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
        free(words);
    }

    return 0;
}