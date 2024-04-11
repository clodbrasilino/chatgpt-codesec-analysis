#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <regex.h>

int match(const char *string) {
    regex_t re;
    if (regcomp(&re, "a.*b$", REG_EXTENDED) != 0) return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0) return 0;
    return 1;
}

int main() {
    char *str1 = "abc";
    char *str2 = "acb";
    printf("%d\n", match(str1)); // 1
    printf("%d\n", match(str2)); // 0
    return 0;
}