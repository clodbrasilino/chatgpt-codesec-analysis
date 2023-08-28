#include <stdio.h>
#include <string.h>
#include <regex.h>

void replace_chars(char *str) {
    regex_t regex;
    regcomp(&regex, "[ ,.]", 0);
    regreplace(&regex, str, ":", str, 0);
    regfree(&regex);
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}