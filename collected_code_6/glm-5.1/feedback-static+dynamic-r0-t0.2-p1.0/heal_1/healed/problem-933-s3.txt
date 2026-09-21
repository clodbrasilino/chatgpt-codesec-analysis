#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (j + 2 >= max_len) {
                break;
            }
            result[j++] = '_';
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            if (j + 1 >= max_len) {
                break;
            }
            result[j++] = camel_str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *inputs[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCaseStringExample123",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    
    return 0;
}