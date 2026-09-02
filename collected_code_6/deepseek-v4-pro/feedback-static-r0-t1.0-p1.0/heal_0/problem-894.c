#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    float *values;
    size_t size;
} FloatTuple;

FloatTuple parse_float_tuple(const char *str) {
    FloatTuple tuple = {NULL, 0};
    
    if (str == NULL) {
        return tuple;
    }
    
    const char *start = strchr(str, '(');
    const char *end = strrchr(str, ')');
    
    if (start == NULL || end == NULL || end <= start) {
        return tuple;
    }
    
    size_t len = end - start - 1;
    if (len == 0) {
        return tuple;
    }
    
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return tuple;
    }
    
    strncpy(buffer, start + 1, len);
    buffer[len] = '\0';
    
    size_t capacity = 4;
    tuple.values = (float *)malloc(capacity * sizeof(float));
    if (tuple.values == NULL) {
        free(buffer);
        tuple.size = 0;
        return tuple;
    }
    
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        
        char *endptr = NULL;
        float val = strtof(token, &endptr);
        
        if (endptr == token || (*endptr != '\0' && *endptr != ' ')) {
            free(tuple.values);
            free(buffer);
            tuple.values = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        if (tuple.size >= capacity) {
            capacity *= 2;
            float *temp = (float *)realloc(tuple.values, capacity * sizeof(float));
            if (temp == NULL) {
                free(tuple.values);
                free(buffer);
                tuple.values = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.values = temp;
        }
        
        tuple.values[tuple.size++] = val;
        token = strtok(NULL, ",");
    }
    
    free(buffer);
    return tuple;
}

int main(void) {
    const char *test = "(3.14, 2.718, 1.414, 0.577)";
    FloatTuple result = parse_float_tuple(test);
    
    if (result.values == NULL) {
        fprintf(stderr, "Failed to parse tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Parsed %zu values:\n", result.size);
    for (size_t i = 0; i < result.size; i++) {
        printf("%.3f ", result.values[i]);
    }
    printf("\n");
    
    free(result.values);
    return EXIT_SUCCESS;
}