#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *convert_camel_to_snake(const char *camel_case_str);

char *convert_camel_to_snake(const char *camel_case_str) {
    if (camel_case_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel_case_str);
    char *snake_case_str = malloc((len * 2) + 1);

    if (snake_case_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case_str[i])) {
            if (i > 0) {
                snake_case_str[j++] = '_';
            }
            snake_case_str[j++] = (char)tolower((unsigned char)camel_case_str[i]);
        } else {
            snake_case_str[j++] = camel_case_str[i];
        }
    }
    
    snake_case_str[j] = '\0';
    return snake_case_str;
}

int main(void) {
    const char *inputs[] = {
        "thisIsCamelCase",
        "CamelCaseString",
        "already_snake_case",
        "short",
        "",
        NULL
    };
    
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < num_inputs; i++) {
        char *output = convert_camel_to_snake(inputs[i]);
        
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else if (inputs[i] != NULL) {
            fprintf(stderr, "Allocation error\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}