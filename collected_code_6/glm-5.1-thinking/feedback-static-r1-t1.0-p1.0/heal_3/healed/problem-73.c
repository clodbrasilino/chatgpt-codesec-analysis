#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

char **split_string_regex(const char *str, const char *pattern, int *out_count) {
    regex_t regex;
    int ret;
    regmatch_t match;
    char **result = NULL;
    int count = 0;
    int capacity = 10;
    const char *ptr = str;
    size_t original_len = 0;
    
    while (str[original_len] != '\0') {
        original_len++;
    }

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
            
            if (token_len > INT_MAX || token_len + 1 < token_len) {
                for (int i = 0; i < count; i++) free(result[i]);
                free(result);
                regfree(&regex);
                return NULL;
            }
            
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

            if (match.rm_so == match.rm_eo) {
                if (*ptr == '\0') {
                    break;
                }
                ptr++;
            }
        } else {
            break;
        }
    }

    size_t remaining_len = original_len - (size_t)(ptr - str);
    
    if (remaining_len + 1 < remaining_len) {
        for (int i = 0; i < count; i++) free(result[i]);
        free(result);
        regfree(&regex);
        return NULL;
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