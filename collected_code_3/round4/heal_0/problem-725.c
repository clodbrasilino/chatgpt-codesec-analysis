#include <stdio.h>
#include <string.h>
#include <regex.h>

void extract_values(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    char pattern[] = "\"([^\"]*)\"";

    regcomp(&regex, pattern, REG_EXTENDED);
    while (regexec(&regex, str, nmatch, pmatch, 0) == 0) {
        int length = pmatch[0].rm_eo - pmatch[0].rm_so;
        char match[length + 1];
        strncpy(match, &str[pmatch[0].rm_so], length);
        match[length] = '\0';
        printf("%s\n", match);
        str += pmatch[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    char str[] = "This is a \"test\". And this is another \"test\".";
    extract_values(str);
    return 0;
}