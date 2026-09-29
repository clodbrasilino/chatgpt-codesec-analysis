#include <stdio.h>
#include <string.h>
#include <regex.h>

void extract_values(char *str) {
    regex_t regex;
    regmatch_t pmatch[2];
    char *pattern = "\"([^\"]*)\"";
    regcomp(&regex, pattern, REG_EXTENDED);
    const char *ptr = str;
    while (!regexec(&regex, ptr, 2, pmatch, 0)) {
        int start = pmatch[1].rm_so + (ptr - str);
        int end = pmatch[1].rm_eo + (ptr - str);
        printf("%.*s\n", (end - start), str + start);
        ptr += pmatch[0].rm_eo;
    }
    regfree(&regex);
}

int main() {
    char str[] = "Hello \"World\"! \"How\" are \"you\"?";
    extract_values(str);
    return 0;
}