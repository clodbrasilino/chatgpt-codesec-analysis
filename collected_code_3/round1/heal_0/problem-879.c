#include <stdio.h>
#include <string.h>
#include <regex.h>

int match(const char *string) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "a.*b$", 0);
    if (ret) {
        printf("Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, string, 0, NULL, 0);
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        printf("Regex match failed\n");
        return 0;
    }

    regfree(&regex);
}

int main() {
    char *test1 = "abc";
    char *test2 = "acb";
    printf("Test 1: %s\n", match(test1) ? "Match" : "No match");
    printf("Test 2: %s\n", match(test2) ? "Match" : "No match");
    return 0;
}