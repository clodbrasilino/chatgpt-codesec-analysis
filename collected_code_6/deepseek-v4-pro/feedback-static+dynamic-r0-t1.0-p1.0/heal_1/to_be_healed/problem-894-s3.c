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

int main() {
    char input[100];
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    Tuple result;
    
    printf("Enter a tuple in format 'float,float': ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        result = string_to_float_tuple(input);
        printf("Tuple: (%f, %f)\n", result.x, result.y);
    }
    
    return 0;
}