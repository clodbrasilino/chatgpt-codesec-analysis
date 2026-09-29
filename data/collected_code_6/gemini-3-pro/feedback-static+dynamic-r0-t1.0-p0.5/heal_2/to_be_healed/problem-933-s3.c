#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char* camel_case) {
    if (!camel_case) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel_case);
    char* snake_case = (char*)malloc(len * 2 + 1);
    if (!snake_case) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0 && islower((unsigned char)camel_case[i - 1])) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    const char* camel = "thisIsACamelCaseString";
    char* snake = camel_to_snake(camel);
    
    if (snake) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Conversion failed or memory allocation error.\n");
        return 1;
    }

    return 0;
}