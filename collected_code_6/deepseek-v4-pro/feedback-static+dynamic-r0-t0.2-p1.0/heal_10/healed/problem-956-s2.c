#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_CAPACITY 10
#define MAX_SEGMENT_SIZE 4096

char **split_at_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    int last_pos = 0;
    int i;
    size_t input_len;
    
    if (input == NULL || count == NULL) {
        return NULL;
    }
    
    input_len = strnlen(input, MAX_SEGMENT_SIZE * 2);
    if (input_len == 0 || input_len >= MAX_SEGMENT_SIZE * 2) {
        return NULL;
    }
    
    result = (char **)malloc((size_t)capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    
    for (i = 0; i <= (int)input_len; i++) {
        if (i == (int)input_len || (i > 0 && isupper((unsigned char)input[i]))) {
            size_t len = (size_t)(i - last_pos);
            if (len > 0) {
                if (size >= capacity) {
                    int new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        int j;
                        for (j = 0; j < size; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **new_result = (char **)realloc(result, (size_t)new_capacity * sizeof(char *));
                    if (new_result == NULL) {
                        int j;
                        for (j = 0; j < size; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }
                
                if (len >= MAX_SEGMENT_SIZE) {
                    int j;
                    for (j = 0; j < size; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                
                if ((size_t)last_pos + len > input_len) {
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
                
                if (len > 0) {
                    size_t available = input_len - (size_t)last_pos;
                    if (len > available) {
                        free(temp);
                        int j;
                        for (j = 0; j < size; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    if (len + 1 > available + 1) {
                        free(temp);
                        int j;
                        for (j = 0; j < size; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    memcpy(temp, input + last_pos, len);
                }
                temp[len] = '\0';
                result[size++] = temp;
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