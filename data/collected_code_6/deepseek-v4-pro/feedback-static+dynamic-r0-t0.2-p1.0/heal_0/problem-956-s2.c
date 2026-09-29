#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    char **result = NULL;
    int capacity = 10;
    int size = 0;
    int last_pos = 0;
    int i;
    char *temp;
    
    if (input == NULL || count == NULL) {
        return NULL;
    }
    
    result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }
    
    for (i = 0; i <= (int)strlen(input); i++) {
        if (i == (int)strlen(input) || 
            (regexec(&regex, (char[]){input[i], '\0'}, 2, matches, 0) == 0 && i > 0)) {
            int len = i - last_pos;
            if (len > 0) {
                if (size >= capacity) {
                    capacity *= 2;
                    char **new_result = (char **)realloc(result, capacity * sizeof(char *));
                    if (new_result == NULL) {
                        int j;
                        for (j = 0; j < size; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = new_result;
                }
                
                temp = (char *)malloc((len + 1) * sizeof(char));
                if (temp == NULL) {
                    int j;
                    for (j = 0; j < size; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                
                strncpy(temp, input + last_pos, len);
                temp[len] = '\0';
                result[size++] = temp;
            }
            last_pos = i;
        }
    }
    
    regfree(&regex);
    *count = size;
    return result;
}

void free_split_result(char **result, int count) {
    int i;
    if (result == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    char **parts;
    int count;
    int i;
    
    parts = split_at_uppercase(test_string, &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }
    
    printf("Original: %s\n", test_string);
    printf("Split parts (%d):\n", count);
    for (i = 0; i < count; i++) {
        printf("  [%d]: %s\n", i, parts[i]);
    }
    
    free_split_result(parts, count);
    return 0;
}