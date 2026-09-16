#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int check_alphanumeric_end(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int ret;
    int result = 0;

    ret = regcomp(&regex, "[A-Za-z0-9]$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *test1 = "Hello World123";
    const char *test2 = "Hello World!";
    const char *test3 = "Test";
    const char *test4 = "Test.";
    const char *test5 = NULL;

    printf("'%s': %d\n", test1, check_alphanumeric_end(test1));
    printf("'%s': %d\n", test2, check_alphanumeric_end(test2));
    printf("'%s': %d\n", test3, check_alphanumeric_end(test3));
    printf("'%s': %d\n", test4, check_alphanumeric_end(test4));
    printf("NULL: %d\n", check_alphanumeric_end(test5));

    return 0;
}