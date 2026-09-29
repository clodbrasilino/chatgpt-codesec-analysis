#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
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
    while (regexec(&regex, temp1, 3, matches, 0) == 0) {
        size_t prefix_len = matches[1].rm_so;
        size_t lower_len = matches[1].rm_eo - matches[1].rm_so;
        size_t upper_len = matches[2].rm_eo - matches[2].rm_so;
        size_t suffix_len = strlen(temp1 + matches[2].rm_eo);

        if (prefix_len + lower_len + 1 + upper_len + suffix_len >= max_len) {
            free(temp1);
            free(temp2);
            regfree(&regex);
            return NULL;
        }

        memcpy(temp2, temp1, prefix_len);
        memcpy(temp2 + prefix_len, temp1 + matches[1].rm_so, lower_len);
        temp2[prefix_len + lower_len] = '_';
        char upper_char = temp1[matches[2].rm_so];
        temp2[prefix_len + lower_len + 1] = upper_char + 32;
        memcpy(temp2 + prefix_len + lower_len + 2, temp1 + matches[2].rm_eo, suffix_len);
        temp2[prefix_len + lower_len + 1 + upper_len + suffix_len] = '\0';

        char *swap = temp1;
        temp1 = temp2;
        temp2 = swap;
    }

    regfree(&regex);
    free(temp2);

    return temp1;
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