#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
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

    char *result = malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            result[j++] = '_';
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            result[j++] = camel_str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "convertCamelCaseToSnakeCase";
    char *result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }
    return 0;
}