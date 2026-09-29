#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} Tuple;

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

char *flatten_tuples(const Tuple *tuples, size_t count, const char *separator) {
    if (tuples == NULL || separator == NULL) {
        return NULL;
    }
    
    size_t total_len = 0;
    size_t sep_len = safe_strlen(separator, 4096);
    
    for (size_t i = 0; i < count; i++) {
        if (tuples[i].key == NULL || tuples[i].value == NULL) {
            return NULL;
        }
        size_t key_len = safe_strlen(tuples[i].key, 4096);
        size_t value_len = safe_strlen(tuples[i].value, 4096);
        
        if (key_len > SIZE_MAX - value_len) {
            return NULL;
        }
        if (total_len > SIZE_MAX - key_len - value_len) {
            return NULL;
        }
        total_len += key_len + value_len;
        
        if (i < count - 1) {
            if (total_len > SIZE_MAX - sep_len) {
                return NULL;
            }
            total_len += sep_len;
        }
    }
    
    if (total_len == SIZE_MAX) {
        return NULL;
    }
    
    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t offset = 0;
    size_t remaining = total_len + 1;
    
    for (size_t i = 0; i < count; i++) {
        size_t key_len = safe_strlen(tuples[i].key, 4096);
        size_t value_len = safe_strlen(tuples[i].value, 4096);
        
        if (key_len >= remaining || key_len > total_len - offset) {
            free(result);
            return NULL;
        }
        if (key_len > 0) {
            memcpy(result + offset, tuples[i].key, key_len);
        }
        offset += key_len;
        remaining -= key_len;
        
        if (value_len >= remaining || value_len > total_len - offset) {
            free(result);
            return NULL;
        }
        if (value_len > 0) {
            memcpy(result + offset, tuples[i].value, value_len);
        }
        offset += value_len;
        remaining -= value_len;
        
        if (i < count - 1) {
            if (sep_len >= remaining || sep_len > total_len - offset) {
                free(result);
                return NULL;
            }
            if (sep_len > 0) {
                memcpy(result + offset, separator, sep_len);
            }
            offset += sep_len;
            remaining -= sep_len;
        }
    }
    
    if (offset > total_len) {
        free(result);
        return NULL;
    }
    
    result[offset] = '\0';
    
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {"name", "John"},
        {"age", "30"},
        {"city", "NYC"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    char *flattened = flatten_tuples(tuples, count, ", ");
    if (flattened == NULL) {
        fprintf(stderr, "Error: Failed to flatten tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("%s\n", flattened);
    
    free(flattened);
    return EXIT_SUCCESS;
}