#include <stdio.h>
#include <regex.h>

int starts_with_substring(const char *str, const char *pattern) {
    regex_t reg;
    int reti;

    if (regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&reg, str, 0, NULL, 0);
    
    regfree(&reg);

    if (reti == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *str = "hello world";
    const char *pattern = "^hello";

    if (starts_with_substring(str, pattern)) {
        printf("The string starts with the substring.\n");
    } else {
        printf("The string does not start with the substring.\n");
    }

    return 0;
}