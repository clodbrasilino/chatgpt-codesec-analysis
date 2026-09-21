#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel_str[len] != '\0') {
        len++;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i]) && islower((unsigned char)camel_str[i - 1])) {
            if (j + 1 >= max_len) {
                free(result);
                return NULL;
            }
            result[j++] = '_';
        }
        if (j >= max_len) {
            free(result);
            return NULL;
        }
        result[j++] = tolower((unsigned char)camel_str[i]);
    }

    if (j >= max_len) {
        free(result);
        return NULL;
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