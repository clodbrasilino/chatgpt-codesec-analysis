#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

static size_t bounded_strlen(const char *s, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return maxlen;
}

static bool safe_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return false;
    }
    *result = a + b;
    return true;
}

char* concatenate_adjacent(const char* tuple[], int size) {
    if (size <= 0 || tuple == NULL) {
        return NULL;
    }
    
    size_t total_len = 0;
    int i;
    size_t *lengths = (size_t *)calloc((size_t)size, sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }
    
    for (i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        size_t len = bounded_strlen(tuple[i], SIZE_MAX);
        if (!safe_add_size(total_len, len, &total_len)) {
            free(lengths);
            return NULL;
        }
        lengths[i] = len;
    }
    
    if (total_len == SIZE_MAX) {
        free(lengths);
        return NULL;
    }
    
    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }
    
    size_t offset = 0;
    
    for (i = 0; i < size - 1; i++) {
        size_t len_i = lengths[i];
        size_t len_i1 = lengths[i + 1];
        
        if (len_i > 0) {
            if (offset > total_len || len_i > total_len - offset) {
                free(result);
                free(lengths);
                return NULL;
            }
            memcpy(result + offset, tuple[i], len_i);
            offset += len_i;
        }
        
        if (len_i1 > 0) {
            if (offset > total_len || len_i1 > total_len - offset) {
                free(result);
                free(lengths);
                return NULL;
            }
            memcpy(result + offset, tuple[i + 1], len_i1);
            offset += len_i1;
        }
    }
    
    free(lengths);
    
    if (offset <= total_len) {
        result[offset] = '\0';
    } else {
        free(result);
        return NULL;
    }
    
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