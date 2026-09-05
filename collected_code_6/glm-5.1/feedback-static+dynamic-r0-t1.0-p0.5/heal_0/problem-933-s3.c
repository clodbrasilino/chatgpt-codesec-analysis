#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = strlen(camel_str) * 2 + 1;
    char *temp1 = malloc(max_len);
    char *temp2 = malloc(max_len);
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        regfree(&regex);
        return NULL;
    }

    strncpy(temp1, camel_str, max_len - 1);
    temp1[max_len - 1] = '\0';

    regmatch_t matches[3];
    while (1) {
        if (regexec(&regex, temp1, 3, matches, 0) != 0) {
            break;
        }

        size_t prefix_len = matches[2].rm_so;
        size_t match_len = matches[2].rm_eo - matches[2].rm_so;

        memcpy(temp2, temp1, prefix_len);
        temp2[prefix_len] = '_';
        for (size_t i = 0; i < match_len; i++) {
            temp2[prefix_len + 1 + i] = temp1[matches[2].rm_so + i] + 32;
        }
        strcpy(temp2 + prefix_len + 1 + match_len, temp1 + matches[2].rm_eo);

        char *swap = temp1;
        temp1 = temp2;
        temp2 = swap;
    }

    regfree(&regex);
    free(temp2);

    size_t final_len = strlen(temp1) + 1;
    char *result = malloc(final_len);
    if (result == NULL) {
        free(temp1);
        return NULL;
    }
    memcpy(result, temp1, final_len);
    
    free(temp1);
    return result;
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "thisIsATest",
        "convertCamelCaseToSnakeCase",
        "already_snake",
        "simple",
        "aB",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *snake = camel_to_snake(inputs[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", inputs[i], snake);
            free(snake);
        }
    }

    return 0;
}