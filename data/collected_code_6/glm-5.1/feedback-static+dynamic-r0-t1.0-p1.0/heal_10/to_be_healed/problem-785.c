#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

IntTuple tuple_string_to_int(const char *str) {
    IntTuple result = {NULL, 0};
    
    if (str == NULL) {
        return result;
    }
    
    const char *p = str;
    if (*p != '(') {
        return result;
    }
    p++;
    
    size_t capacity = 1;
    const char *scan = p;
    while (*scan != '\0' && *scan != ')') {
        if (*scan == ',') {
            capacity++;
        }
        scan++;
    }
    
    if (*scan != ')' || scan == p) {
        return result;
    }
    
    result.elements = (int *)malloc(capacity * sizeof(int));
    if (result.elements == NULL) {
        return result;
    }
    
    size_t buffer_size = scan - p + 1;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        free(result.elements);
        result.elements = NULL;
        return result;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, p, buffer_size - 1);
    buffer[buffer_size - 1] = '\0';
    
    char *saveptr = NULL;
    char *token = strtok_r(buffer, ",", &saveptr);
    
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        
        if (*token == '\0') {
            free(result.elements);
            free(buffer);
            result.elements = NULL;
            result.count = 0;
            return result;
        }
        
        char *endptr = NULL;
        errno = 0;
        long val = strtol(token, &endptr, 10);
        
        if (errno != 0 || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(result.elements);
            free(buffer);
            result.elements = NULL;
            result.count = 0;
            return result;
        }
        
        result.elements[result.count] = (int)val;
        result.count++;
        
        token = strtok_r(NULL, ",", &saveptr);
    }
    
    free(buffer);
    return result;
}

int main(void) {
    const char *input = "(10, -20, 30, 40)";
    IntTuple t = tuple_string_to_int(input);
    
    if (t.elements != NULL) {
        for (size_t i = 0; i < t.count; i++) {
            printf("%d ", t.elements[i]);
        }
        printf("\n");
        free(t.elements);
    } else {
        printf("Conversion failed\n");
    }
    
    return 0;
}