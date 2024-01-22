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

    if (str) {
        size_t len = strlen(str);

        char *new_str = (char*)calloc(len+1, sizeof(char));
        if (!new_str)
            return;

        strncpy(new_str, str, len);

        while (regexec(&regex, new_str, nmatch, pmatch, 0) == 0) {
            memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo + 1);
            new_str[pmatch[0].rm_so] = replace[0];
        }

        len = strlen(new_str);

        if (strlen(str) >= len) {
            strncpy(str, new_str, len);
            str[len] = '\0';
        }

        free(new_str);
        regfree(&regex);
    }
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}