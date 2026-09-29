#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int find_lowercase_underscore_sequences(const char *str, char ***results, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t capacity = 10;
    size_t len;
    char *substring;

    *count = 0;
    *results = malloc(capacity * sizeof(char *));
    if (*results == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+_[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(*results);
        *results = NULL;
        return -1;
    }

    const char *cursor = str;
    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            for (size_t i = 0; i < *count; i++) {
                free((*results)[i]);
            }
            free(*results);
            *results = NULL;
            *count = 0;
            regfree(&regex);
            return -1;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(*results, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free((*results)[i]);
                }
                free(*results);
                *results = NULL;
                *count = 0;
                regfree(&regex);
                return -1;
            }
            *results = temp;
        }

        len = match.rm_eo - match.rm_so;
        substring = malloc(len + 1);
        if (substring == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free((*results)[i]);
            }
            free(*results);
            *results = NULL;
            *count = 0;
            regfree(&regex);
            return -1;
        }

        memcpy(substring, cursor + match.rm_so, len);
        substring[len] = '\0';

        (*results)[*count] = substring;
        (*count)++;

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

void free_results(char **results, size_t count) {
    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(results[i]);
        }
        free(results);
    }
}

int main(void) {
    const char *text = "hello_world abc_xyz test_case 123_bad 456_aBc valid_match";
    char **results = NULL;
    size_t count = 0;

    if (find_lowercase_underscore_sequences(text, &results, &count) == 0) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", results[i]);
        }
        free_results(results, count);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}