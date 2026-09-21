#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

char **split_string_regex(const char *str, size_t str_len, const char *pattern, int *out_count) {
    if (str == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    regmatch_t match;
    char **result = NULL;
    int count = 0;
    int capacity = 10;
    const char *ptr = str;
    size_t ptr_len = str_len;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (ptr_len > 0) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == 0 && match.rm_so >= 0 && (size_t)match.rm_eo <= ptr_len) {
            if (match.rm_eo == 0) {
                break;
            }
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
            ptr_len -= match.rm_eo;
        } else {
            break;
        }
    }

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
    result[count] = malloc(ptr_len + 1);
    if (result[count] == NULL) {
        for (int i = 0; i < count; i++) free(result[i]);
        free(result);
        regfree(&regex);
        return NULL;
    }
    snprintf(result[count], ptr_len + 1, "%.*s", (int)ptr_len, ptr);
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
    size_t str_len = sizeof("Hello;world|this,is,a|test") - 1;
    const char *pattern = "[;,|]";
    int count = 0;

    char **tokens = split_string_regex(str, str_len, pattern, &count);
    if (tokens != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
        }
        free_split_result(tokens, count);
    }

    return 0;
}