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
        regfree(&regex);
        free(temp1);
        free(temp2);
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
        size_t match1_len = matches[1].rm_eo - matches[1].rm_so;
        size_t match2_len = matches[2].rm_eo - matches[2].rm_so;
        size_t suffix_len = strlen(temp1 + matches[2].rm_eo);

        if (prefix_len + match1_len + 1 + match2_len + suffix_len >= max_len) {
            break;
        }

        memcpy(temp2, temp1, prefix_len);
        temp2[prefix_len] = '\0';

        strncat(temp2, temp1 + matches[1].rm_so, match1_len);
        strncat(temp2, "_", 1);
        strncat(temp2, temp1 + matches[2].rm_so, match2_len);
        strncat(temp2, temp1 + matches[2].rm_eo, max_len - strlen(temp2) - 1);

        char *swap = temp1;
        temp1 = temp2;
        temp2 = swap;
    }

    regfree(&regex);
    free(temp2);

    return temp1;
}

int main(void) {
    const char *input = "camelCaseStringExample123";
    char *result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}