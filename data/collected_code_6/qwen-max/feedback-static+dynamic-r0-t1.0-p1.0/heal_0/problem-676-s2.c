#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char result[1024] = "";
    int pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0)) {
        return;
    }

    while (regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            strncat(result, str + pos, match[0].rm_so);
            strcat(result, "");
        }
        pos += match[0].rm_eo;
    }
    if (pos < strlen(str)) {
        strncat(result, str + pos, strlen(str) - pos);
    }
    strncpy(str, result, sizeof(result));
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input);
    printf("%s\n", input);
    return 0;
}