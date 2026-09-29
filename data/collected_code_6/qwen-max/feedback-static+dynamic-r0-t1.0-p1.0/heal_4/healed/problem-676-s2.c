#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t match[1];
    char result[1024] = "";
    int pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED)) {
        return;
    }

    while (pos < str_len && regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            size_t len = snprintf(result + strlen(result), sizeof(result) - strlen(result) - 1, "%.*s", (int)match[0].rm_so, str + pos);
            (void)len;
        }
        pos += match[0].rm_eo;
    }

    if (pos < (int)str_len && (strlen(result) + str_len - pos) < sizeof(result) - 1) {
        size_t len = snprintf(result + strlen(result), sizeof(result) - strlen(result) - 1, "%s", str + pos);
        (void)len;
    }

    if (str_len > 0) {
        strncpy(str, result, str_len - 1);
        str[str_len - 1] = '\0';
    }
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}