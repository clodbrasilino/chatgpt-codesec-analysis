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

static int checked_add_size(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return -1;
    }
    *result = a + b;
    return 0;
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
        
        size_t pair_len;
        if (checked_add_size(key_len, value_len, &pair_len) != 0) {
            return NULL;
        }
        if (checked_add_size(total_len, pair_len, &total_len) != 0) {
            return NULL;
        }
        
        if (i < count - 1) {
            if (checked_add_size(total_len, sep_len, &total_len) != 0) {
                return NULL;
            }
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
        
        if (key_len > 0) {
            if (key_len >= remaining || offset > total_len - key_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, tuples[i].key, key_len);
            offset += key_len;
            remaining -= key_len;
        }
        
        if (value_len > 0) {
            if (value_len >= remaining || offset > total_len - value_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, tuples[i].value, value_len);
            offset += value_len;
            remaining -= value_len;
        }
        
        if (i < count - 1 && sep_len > 0) {
            if (sep_len >= remaining || offset > total_len - sep_len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, separator, sep_len);
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