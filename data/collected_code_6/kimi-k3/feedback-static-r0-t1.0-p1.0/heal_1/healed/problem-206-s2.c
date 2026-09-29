#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        size_t len = 0;
        const char* p = tuple[i];
        while (p[len] != '\0') {
            len++;
        }
        total_len += len;
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    
    for (i = 0; i < size - 1; i++) {
        size_t len_i = 0;
        const char* p_i = tuple[i];
        while (p_i[len_i] != '\0') {
            len_i++;
        }
        
        size_t len_i1 = 0;
        const char* p_i1 = tuple[i + 1];
        while (p_i1[len_i1] != '\0') {
            len_i1++;
        }
        
        if (offset + len_i + len_i1 < total_len + 1) {
            memcpy(result + offset, tuple[i], len_i);
            offset += len_i;
            memcpy(result + offset, tuple[i + 1], len_i1);
            offset += len_i1;
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