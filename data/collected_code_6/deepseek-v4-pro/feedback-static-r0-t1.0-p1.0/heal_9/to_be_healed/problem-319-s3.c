#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int find_five_char_words(const char *input, char ***matches, int *match_count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    int ret;
    size_t capacity = 10;
    int count = 0;
    char **result = NULL;
    const char *cursor = input;

    if (!input || !matches || !match_count) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }

    result = malloc(capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if ((size_t)count >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                for (int i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            char **temp = realloc(result, new_capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
            capacity = new_capacity;
        }

        if (pmatch[0].rm_so == -1 || pmatch[0].rm_eo == -1 ||
            pmatch[0].rm_so >= pmatch[0].rm_eo) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        int len = pmatch[0].rm_eo - pmatch[0].rm_so;

        result[count] = malloc((size_t)len + 1);
        if (!result[count]) {
            for (int i = 0; i < count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[count], cursor + pmatch[0].rm_so, (size_t)len);
        result[count][len] = '\0';

        count++;

        cursor += pmatch[0].rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    *matches = result;
    *match_count = count;

    return 0;
}

void free_matches(char **matches, int count) {
    if (matches) {
        for (int i = 0; i < count; i++) {
            free(matches[i]);
        }
        free(matches);
    }
}

int main(void) {
    const char *text = "Hello world this is a test with words like apple trees house mouse happy";
    char **matches = NULL;
    int count = 0;

    if (find_five_char_words(text, &matches, &count) == 0) {
        printf("Found %d five-character words:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", matches[i]);
        }
        free_matches(matches, count);
    } else {
        printf("Error processing string\n");
    }

    return 0;
}