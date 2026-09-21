#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char **split_regex(const char *str, const char *pattern, int *count) {
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    int capacity = 10;
    int size = 0;
    const char *cursor;
    const char *end;
    
    if (!str || !pattern || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    end = str;
    while (*end) end++;
    
    if (end == str) {
        result = (char **)malloc(sizeof(char *));
        if (!result) {
            *count = 0;
            return NULL;
        }
        result[0] = (char *)malloc(sizeof(char));
        if (!result[0]) {
            free(result);
            *count = 0;
            return NULL;
        }
        result[0][0] = '\0';
        *count = 1;
        return result;
    }
    
    cursor = str;
    
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        *count = 0;
        return NULL;
    }
    
    result = (char **)malloc(capacity * sizeof(char *));
    if (!result) {
        regfree(&regex);
        *count = 0;
        return NULL;
    }
    
    while (cursor <= end && regexec(&regex, cursor, 1, &match, 0) == 0) {
        const char *token_start = cursor;
        size_t token_len;
        
        if (match.rm_so == -1) {
            token_len = (size_t)(end - cursor);
        } else {
            token_len = (size_t)match.rm_so;
        }
        
        if (size == capacity) {
            capacity *= 2;
            char **temp = (char **)realloc(result, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }
        
        result[size] = (char *)malloc((token_len + 1) * sizeof(char));
        if (!result[size]) {
            for (int i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        
        if (token_len > 0) {
            for (size_t i = 0; i < token_len; i++) {
                result[size][i] = token_start[i];
            }
        }
        result[size][token_len] = '\0';
        size++;
        
        if (match.rm_eo > 0 || match.rm_so > 0) {
            cursor += match.rm_so + match.rm_eo;
        } else {
            if (cursor < end) {
                cursor++;
            } else {
                break;
            }
        }
    }
    
    if (cursor < end) {
        size_t remaining_len = (size_t)(end - cursor);
        
        if (size == capacity) {
            capacity *= 2;
            char **temp = (char **)realloc(result, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }
        
        result[size] = (char *)malloc((remaining_len + 1) * sizeof(char));
        if (!result[size]) {
            for (int i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        
        for (size_t i = 0; i < remaining_len; i++) {
            result[size][i] = cursor[i];
        }
        result[size][remaining_len] = '\0';
        size++;
    } else if (cursor == end && match.rm_so == 0 && match.rm_eo == 0 && size > 0) {
        if (size == capacity) {
            capacity *= 2;
            char **temp = (char **)realloc(result, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }
        
        result[size] = (char *)malloc(sizeof(char));
        if (!result[size]) {
            for (int i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        
        result[size][0] = '\0';
        size++;
    }
    
    regfree(&regex);
    *count = size;
    return result;
}

static void free_split_result(char **result, int count) {
    if (result) {
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char *text = "apple,banana;cherry:date|elderberry";
    const char *pattern = "[,;:|]";
    int count = 0;
    
    char **tokens = split_regex(text, pattern, &count);
    
    if (tokens) {
        printf("Split results (%d tokens):\n", count);
        for (int i = 0; i < count; i++) {
            printf("Token %d: %s\n", i, tokens[i]);
        }
        free_split_result(tokens, count);
    } else {
        printf("Failed to split string\n");
    }
    
    return 0;
}