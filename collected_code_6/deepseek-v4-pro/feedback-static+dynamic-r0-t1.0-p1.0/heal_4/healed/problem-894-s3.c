#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    float x;
    float y;
} Tuple;

Tuple string_to_float_tuple(const char *str) {
    Tuple result = {0.0f, 0.0f};
    char *token;
    char *input_copy;
    char *rest;
    
    if (str == NULL) {
        return result;
    }
    
    input_copy = strdup(str);
    if (input_copy == NULL) {
        return result;
    }
    
    rest = input_copy;
    token = strtok_r(rest, ",", &rest);
    if (token != NULL) {
        char *endptr;
        errno = 0;
        result.x = strtof(token, &endptr);
        if (endptr == token || errno == ERANGE) {
            result.x = 0.0f;
        }
    }
    
    token = strtok_r(NULL, ",", &rest);
    if (token != NULL) {
        char *endptr;
        errno = 0;
        result.y = strtof(token, &endptr);
        if (endptr == token || errno == ERANGE) {
            result.y = 0.0f;
        }
    }
    
    free(input_copy);
    return result;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t input_len;
    
    printf("Enter a tuple in format 'float,float': ");
    input_len = getline(&input, &buffer_size, stdin);
    
    if (input_len != -1) {
        if (input_len > 0 && input[input_len - 1] == '\n') {
            input[input_len - 1] = '\0';
            input_len--;
        }
        
        if (input_len > 0) {
            Tuple result = string_to_float_tuple(input);
            printf("Tuple: (%f, %f)\n", result.x, result.y);
        }
    }
    
    free(input);
    return 0;
}