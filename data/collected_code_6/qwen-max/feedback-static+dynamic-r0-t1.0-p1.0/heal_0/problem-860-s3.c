#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

bool isEndingWithAlphanumeric(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[^\\w]*[\\w]+$", REG_EXTENDED);
    if (ret) {
        return false;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}

int main() {
    const char *test1 = "HelloWorld123";
    const char *test2 = "Hello World!123";
    const char *test3 = "!@#";

    printf("%s: %s\n", test1, isEndingWithAlphanumeric(test1) ? "True" : "False");
    printf("%s: %s\n", test2, isEndingWithAlphanumeric(test2) ? "True" : "False");
    printf("%s: %s\n", test3, isEndingWithAlphanumeric(test3) ? "True" : "False");

    return 0;
}