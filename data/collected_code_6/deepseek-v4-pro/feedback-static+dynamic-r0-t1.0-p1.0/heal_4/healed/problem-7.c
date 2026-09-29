#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int find_words(const char *text, char ***words, size_t *count) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;
    int ret;
    size_t capacity = 10;
    char **result;

    *count = 0;
    *words = NULL;

    ret = regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED);
    if (ret) {
        return -1;
    }

    result = malloc(capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t length = match.rm_eo - match.rm_so;
        if (length == 0) {
            break;
        }
        if (*count >= capacity) {
            char **temp;
            if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                size_t i;
                for (i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            capacity *= 2;
            temp = realloc(result, capacity * sizeof(char *));
            if (!temp) {
                size_t i;
                for (i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
        }

        if (length > SIZE_MAX - 1) {
            size_t i;
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        result[*count] = malloc(length + 1);
        if (!result[*count]) {
            size_t i;
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        memcpy(result[*count], p + match.rm_so, length);
        result[*count][length] = '\0';
        (*count)++;
        p += match.rm_eo;
    }

    regfree(&regex);
    *words = result;
    return 0;
}

int main(void) {
    const char *text = "This is a test string with several words like apple banana cat dog elephant";
    char **words;
    size_t count;
    size_t i;
    int ret;

    ret = find_words(text, &words, &count);
    if (ret != 0) {
        fprintf(stderr, "Error finding words\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}