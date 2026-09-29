#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string_regex(const char *str, const char *pattern, int *out_count) {
    regex_t regex;
    int ret;
    regmatch_t match;
    char **result = NULL;
    int count = 0;
    int capacity = 10;
    const char *ptr = str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == 0) {
            size_t token_len = (size_t)match.rm_so;
            if (count >= capacity) {
                capacity *= 2;
                char **temp = realloc(result, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (int i = 0; i < count; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            result[count] = malloc(token_len + 1);
            if (result[count] == NULL) {
                for (int i = 0; i < count; i++) free(result[i]);
                free(result);
                regfree(&regex);
                return NULL;
            }
            snprintf(result[count], token_len + 1, "%.*s", (int)token_len, ptr);
            count++;
            ptr += match.rm_eo;
        } else {
            break;
        }
    }

    size_t remaining_len = str_len - (size_t)(ptr - str);
    if (count >= capacity) {
        capacity += 1;
        char **temp = realloc(result, capacity * sizeof(char *));
        if (temp == NULL) {
            for (int i = 0; i < count; i++) free(result[i]);
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
    }
    result[count] = malloc(remaining_len + 1);
    if (result[count] == NULL) {
        for (int i = 0; i < count; i++) free(result[i]);
        free(result);
        regfree(&regex);
        return NULL;
    }
    snprintf(result[count], remaining_len + 1, "%s", ptr);
    count++;

    *out_count = count;
    regfree(&regex);
    return result;
}

void free_split_result(char **result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *str = "Hello;world|this,is,a|test";
    const char *pattern = "[;,|]";
    int count = 0;

    char **tokens = split_string_regex(str, pattern, &count);
    if (tokens != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
        }
        free_split_result(tokens, count);
    }

    return 0;
}