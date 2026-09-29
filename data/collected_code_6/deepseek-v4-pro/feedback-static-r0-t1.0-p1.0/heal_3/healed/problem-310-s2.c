#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

static char *trim_whitespace(char *str) {
    while (*str == ' ') str++;
    char *start = str;
    while (*str != '\0') {
        str++;
    }
    char *end = str - 1;
    while (end > start && *end == ' ') {
        end--;
    }
    *(end + 1) = '\0';
    return start;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.count = 0;
    
    if (str == NULL) {
        return tuple;
    }
    
    size_t len = safe_strlen(str, 4096);
    if (len >= 4096) {
        return tuple;
    }
    
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }
    
    size_t i;
    for (i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';
    
    size_t capacity = 0;
    char *saveptr = NULL;
    char *token = strtok_r(copy, ",", &saveptr);
    
    while (token != NULL) {
        token = trim_whitespace(token);
        
        size_t token_len = safe_strlen(token, 1024);
        if (token_len >= 1024) {
            for (size_t j = 0; j < tuple.count; j++) {
                free(tuple.elements[j]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }
        
        if (tuple.count >= capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_elements = (char **)realloc(tuple.elements, new_capacity * sizeof(char *));
            if (new_elements == NULL) {
                for (size_t j = 0; j < tuple.count; j++) {
                    free(tuple.elements[j]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.elements = new_elements;
            capacity = new_capacity;
        }
        
        tuple.elements[tuple.count] = (char *)malloc(token_len + 1);
        if (tuple.elements[tuple.count] == NULL) {
            for (size_t j = 0; j < tuple.count; j++) {
                free(tuple.elements[j]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }
        
        for (size_t j = 0; j < token_len; j++) {
            tuple.elements[tuple.count][j] = token[j];
        }
        tuple.elements[tuple.count][token_len] = '\0';
        tuple.count++;
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->count = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple tuple = string_to_tuple(input);
    
    if (tuple.elements != NULL) {
        printf("Tuple elements (%zu):\n", tuple.count);
        for (size_t i = 0; i < tuple.count; i++) {
            printf("  [%zu]: %s\n", i, tuple.elements[i]);
        }
        free_tuple(&tuple);
    } else {
        printf("Failed to convert string to tuple\n");
    }
    
    return 0;
}