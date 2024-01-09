#include <stdio.h>
#include <regex.h>

void replaceSpaces(char *str) {
    regex_t regex;
    regmatch_t substr;

    regcomp(&regex, "\\s", REG_EXTENDED);
    while (regexec(&regex, str, 1, &substr, 0) == 0) {
        if (str[substr.rm_so] == ' ') {
            str[substr.rm_so] = '_';
        } else if (str[substr.rm_so] == '_') {
            str[substr.rm_so] = ' ';
        }
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello world! This is a test string.";
    replaceSpaces(str);
    printf("%s\n", str);
    return 0;
}