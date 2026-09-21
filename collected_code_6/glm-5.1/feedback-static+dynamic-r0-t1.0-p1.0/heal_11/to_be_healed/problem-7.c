#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_long_words(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[1];
    int ret;
    char **results = NULL;
    size_t capacity = 0;
    *count = 0;

    ret = regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    const char *p = str;
    while (regexec(&regex, p, 1, matches, 0) == 0) {
        if (matches[0].rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity = (capacity == 0) ? 8 : capacity * 2;
            char **temp = realloc(results, capacity * sizeof(char *));
            if (!temp) {
                regfree(&regex);
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                return NULL;
            }
            results = temp;
        }

        size_t len = matches[0].rm_eo - matches[0].rm_so;
        char *word = malloc(len + 1);
        if (!word) {
            regfree(&regex);
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            return NULL;
        }

        if (len > 0) {
            size_t copy_len = len;
            if (copy_len > SIZE_MAX - 1) {
                copy_len = SIZE_MAX - 1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, p + matches[0].rm_so, copy_len);
        }
        word[len] = '\0';

        results[*count] = word;
        (*count)++;

        p += matches[0].rm_eo;
    }

    regfree(&regex);
    return results;
}

int main(void) {
    const char *text = "This is a test string with several words of different lengths.";
    size_t count;
    char **words = find_long_words(text, &count);

    if (!words) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }

    free(words);
    return 0;
}