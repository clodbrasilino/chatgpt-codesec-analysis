#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    if (len == 0) {
        char *output = malloc(1);
        if (output == NULL) {
            return NULL;
        }
        output[0] = '\0';
        return output;
    }
    
    size_t max_len = len * 2 + 1;
    char *output = malloc(max_len);
    if (output == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0 && input[i-1] != '_') {
                output[j++] = '_';
            }
            output[j++] = tolower((unsigned char)input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    
    char *result = realloc(output, j + 1);
    if (result == NULL) {
        free(output);
        return NULL;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "pythonLanguage",
        "pythonProgram",
        "programmingLanguage",
        "camelCaseString",
        "helloWorld",
        "a",
        "ABC",
        "alreadySnakeCase",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    
    return 0;
}