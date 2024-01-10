#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_chars(char *str) {
    const char *replace = ":";
    regex_t regex;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    regcomp(&regex, "[ ,.]", REG_EXTENDED);

    if (str == NULL || str[strcspn(str, "\0")] != '\0') {
        return;
    }

    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str == NULL) {
        return;
    }

    strncpy(new_str, str, len);
    new_str[len - 1] = '\0';

    while (regexec(&regex, new_str, nmatch, pmatch, 0) == 0) {
        int size = pmatch[0].rm_eo - pmatch[0].rm_so;
        memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo + 1);
        new_str[pmatch[0].rm_so] = replace[0];
        len = strlen(new_str) + 1;
    }

    strncpy(str, new_str, len);
    str[len - 1] = '\0';

    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}