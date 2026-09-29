#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(char *str) {
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE)) {
        return -1;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        regfree(&regex);
        return -1;
    }
    result[0] = '\0';

    int j = 0;
    for (size_t i = 0; i < len; ++i) {
        if (regexec(&regex, &str[i], 0, NULL, 0) != 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    free(str);
    str = (char *)realloc(result, j + 1);
    if (!str) {
        free(result);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char *str = strdup("Hello!@# World$%^&*()_+");
    if (remove_non_alphanumeric(str) == 0) {
        printf("%s\n", str);
    } else {
        printf("Error occurred.\n");
    }
    free(str);
    return 0;
}