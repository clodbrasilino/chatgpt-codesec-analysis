#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(char *str) {
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE))
        return -1;

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        regfree(&regex);
        return -1;
    }

    int i = 0, j = 0;
    while (i < (int)len) {
        if (regexec(&regex, &str[i], 0, NULL, 0)) {
            result[j++] = str[i];
            i++;
        } else {
            char tmp_buff[100];
            regerror(REG_NOMATCH, &regex, tmp_buff, sizeof(tmp_buff));
            i += strlen(tmp_buff);
        }
    }
    result[j] = '\0';

    free(str);
    str = malloc(j + 1);
    if (!str) {
        free(result);
        regfree(&regex);
        return -1;
    }
    strcpy(str, result);
    free(result);
    regfree(&regex);

    return 0;
}

int main() {
    char *str = "Hello!@# World$%^&*()_+";
    if (remove_non_alphanumeric(str) == 0) {
        printf("%s\n", str);
    } else {
        printf("Error occurred.\n");
    }
    free(str);
    return 0;
}