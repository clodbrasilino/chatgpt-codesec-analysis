#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    char **result = NULL;
    int capacity = 0;
    int start = 0;
    int i = 0;
    int len = strlen(input);
    
    *count = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }
    
    result = malloc(sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    capacity = 1;
    
    while (i < len) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            int match_pos = i + matches[0].rm_so;
            int segment_len = match_pos - start;
            
            if (segment_len > 0) {
                if (*count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(result, capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }
                
                result[*count] = malloc(segment_len + 1);
                if (result[*count] == NULL) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                strncpy(result[*count], input + start, segment_len);
                result[*count][segment_len] = '\0';
                (*count)++;
            }
            
            start = match_pos;
            i = match_pos + 1;
        } else {
            i++;
        }
    }
    
    if (start < len) {
        int segment_len = len - start;
        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }
        
        result[*count] = malloc(segment_len + 1);
        if (result[*count] == NULL) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        strncpy(result[*count], input + start, segment_len);
        result[*count][segment_len] = '\0';
        (*count)++;
    }
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);
    
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);
    
    return 0;
}