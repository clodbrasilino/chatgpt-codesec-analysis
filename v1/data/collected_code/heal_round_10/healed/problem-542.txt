#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_chars(char *str) {
    const char *replace = ":";

    if (str != NULL) {
        size_t len = strnlen(str, 10000); 

        regex_t regex;
        regmatch_t pmatch[1];
        regcomp(&regex, "[ ,.]", REG_EXTENDED);

        char *new_str = (char*)calloc(len+2, sizeof(char));
        if (!new_str)
            return;

        if (len < 10000) {
            memcpy(new_str, str, len);
        } else {
            memcpy(new_str, str, 9999);
            new_str[9999]='\0';
            len = 9999;
        }
        

        while (regexec(&regex, new_str, 1, pmatch, 0) == 0) {
            memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo + 1);
            new_str[pmatch[0].rm_so] = replace[0];
            len = strnlen(new_str, 10000);
        }

        new_str[len] = '\0';

        len = strnlen(new_str, 10000);
        size_t str_len = strnlen(str, 10000);

        if (str_len >= len) {
            if (len < 10000) {
                memcpy(str, new_str, len);
                str[len] = '\0';
            } else {
                memcpy(str, new_str, 9999);
                str[9999] = '\0';
            }
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