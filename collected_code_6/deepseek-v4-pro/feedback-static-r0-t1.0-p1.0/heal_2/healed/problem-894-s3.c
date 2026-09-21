#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        result.x = strtof(token, NULL);
    }
    
    token = strtok_r(NULL, ",", &rest);
    if (token != NULL) {
        result.y = strtof(token, NULL);
    }
    
    free(input_copy);
    return result;
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;
    
    printf("Enter a tuple in format 'float,float': ");
    chars_read = getline(&input, &bufsize, stdin);
    
    if (chars_read != -1) {
        if (chars_read > 0 && input[chars_read - 1] == '\n') {
            input[chars_read - 1] = '\0';
        }
        
        Tuple result = string_to_float_tuple(input);
        printf("Tuple: (%f, %f)\n", result.x, result.y);
    }
    
    free(input);
    return 0;
}