#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* concatenate_adjacent(const char* tuple[], int size) {
    if (size <= 0 || tuple == NULL) {
        return NULL;
    }
    
    size_t total_len = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(tuple[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            return NULL;
        }
        if (total_len > SIZE_MAX - len) {
            return NULL;
        }
        total_len += len;
    }
    
    if (total_len == SIZE_MAX) {
        return NULL;
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    
    for (i = 0; i < size - 1; i++) {
        size_t len_i = strnlen(tuple[i], SIZE_MAX);
        size_t len_i1 = strnlen(tuple[i + 1], SIZE_MAX);
        
        if (len_i == SIZE_MAX || len_i1 == SIZE_MAX) {
            free(result);
            return NULL;
        }
        
        if (offset + len_i + len_i1 < total_len + 1) {
            if (offset + len_i <= total_len) {
                if (len_i <= total_len - offset) {
                    memcpy(result + offset, tuple[i], len_i);
                    offset += len_i;
                }
            }
            if (offset + len_i1 <= total_len) {
                if (len_i1 <= total_len - offset) {
                    memcpy(result + offset, tuple[i + 1], len_i1);
                    offset += len_i1;
                }
            }
        }
    }
    
    result[offset] = '\0';
    
    return result;
}

int main(void) {
    const char* tuple[] = {"Hello", "World", "C", "Programming"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    char* concatenated = concatenate_adjacent(tuple, size);
    
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}