#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char* camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel_case);
    if (len == 0) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t new_len = len;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            new_len++;
        }
    }

    char* snake_case = (char*)malloc(new_len + 1);
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = camel_case[i];
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    const char* example1 = "camelCaseString";
    const char* example2 = "Already_Snake_Case";
    const char* example3 = "Simple";

    char* res1 = camel_to_snake(example1);
    char* res2 = camel_to_snake(example2);
    char* res3 = camel_to_snake(example3);

    if (res1) {
        printf("%s -> %s\n", example1, res1);
        free(res1);
    }
    
    if (res2) {
        printf("%s -> %s\n", example2, res2);
        free(res2);
    }
    
    if (res3) {
        printf("%s -> %s\n", example3, res3);
        free(res3);
    }

    return 0;
}