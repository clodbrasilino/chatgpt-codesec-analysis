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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'input_len' can be reduced. [variableScope]
     */
    size_t input_len;
    
    printf("Enter a tuple in format 'float,float': ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        input_len = strlen(input);
        if (input_len > 0 && input[input_len - 1] == '\n') {
            input[input_len - 1] = '\0';
            input_len--;
        } else {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == EOF) break;
            }
        }
        
        if (input_len > 0 && input_len < sizeof(input)) {
            Tuple result = string_to_float_tuple(input);
            printf("Tuple: (%f, %f)\n", result.x, result.y);
        }
    }
    
    return 0;
}