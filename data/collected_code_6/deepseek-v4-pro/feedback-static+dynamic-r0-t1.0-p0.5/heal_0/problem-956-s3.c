#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** split_at_uppercase(const char* input, int* count) {
    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "[A-Z]";
    int input_len = strlen(input);
    int capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        *count = 0;
        return NULL;
    }
    
    *count = 0;
    int start = 0;
    int i;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        *count = 0;
        return NULL;
    }
    
    for (i = 0; i <= input_len; i++) {
        int is_uppercase = 0;
        if (i < input_len) {
            if (regexec(&regex, input + i, 1, matches, 0) == 0 && matches[0].rm_so == 0) {
                is_uppercase = 1;
            }
        }
        
        if (is_uppercase && i > start) {
            if (*count >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    *count = 0;
                    return NULL;
                }
                result = temp;
            }
            
            int len = i - start;
            result[*count] = malloc((len + 1) * sizeof(char));
            if (!result[*count]) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            strncpy(result[*count], input + start, len);
            result[*count][len] = '\0';
            (*count)++;
            start = i;
        }
    }
    
    if (start < input_len) {
        if (*count >= capacity) {
            capacity *= 2;
            char** temp = realloc(result, capacity * sizeof(char*));
            if (!temp) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }
        
        int len = input_len - start;
        result[*count] = malloc((len + 1) * sizeof(char));
        if (!result[*count]) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        strncpy(result[*count], input + start, len);
        result[*count][len] = '\0';
        (*count)++;
    }
    
    regfree(&regex);
    return result;
}

int main() {
    const char* test_string = "HelloWorldThisIsATest";
    int count = 0;
    char** parts = split_at_uppercase(test_string, &count);
    
    if (parts) {
        printf("Split parts (%d):\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("Failed to split string\n");
    }
    
    return 0;
}