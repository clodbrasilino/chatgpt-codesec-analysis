#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 10;
    int size = 0;
    int last_pos = 0;
    int i;
    size_t input_len;
    
    if (input == NULL || count == NULL) {
        return NULL;
    }
    
    input_len = strlen(input);
    
    result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    
    for (i = 0; i <= (int)input_len; i++) {
        if (i == (int)input_len || (i > 0 && isupper((unsigned char)input[i]))) {
            size_t len = (size_t)(i - last_pos);
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
                        return NULL;
                    }
                    result = new_result;
                }
                
                if (len >= 4096) {
                    int j;
                    for (j = 0; j < size; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                char *temp = (char *)malloc((len + 1) * sizeof(char));
                if (temp == NULL) {
                    int j;
                    for (j = 0; j < size; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                if (last_pos + (int)len <= (int)input_len) {
                    memcpy(temp, input + last_pos, len);
                    temp[len] = '\0';
                    result[size++] = temp;
                } else {
                    free(temp);
                    int j;
                    for (j = 0; j < size; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
            }
            last_pos = i;
        }
    }
    
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