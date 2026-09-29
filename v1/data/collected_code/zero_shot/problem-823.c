#include <stdio.h>
#include <regex.h>

int startsWithRegex(const char *string, const char *pattern) {
    regex_t regex;
    int ret;

    if (regcomp(&regex, pattern, REG_NOSUB | REG_EXTENDED) != 0) {
        return -1;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == REG_NOMATCH) {
        return 0;
    }

    return 1;
}

int main() {
    const char *string = "stackoverflow";
    const char *pattern = "^stack";
    int result = startsWithRegex(string, pattern);

    if (result == 1) {
        printf("The string starts with the substring.\n");
    } else if (result == 0) {
        printf("The string does not start with the substring.\n");
    } else {
        printf("An error occurred.\n");
    }

    return 0;
}