#include <stdio.h>
#include <string.h>
#include <regex.h>

int is_ending_alphanumeric(const char *str) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t len = strlen(str);
    
    if (len == 0) {
        return 0;
    }
    
    ret = regcomp(&regex, ".*[A-Za-z0-9]$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, str, 1, &match, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    const char *test1 = "hello123";
    const char *test2 = "hello!";
    const char *test3 = "test_";
    const char *test4 = "abcDEF456";
    const char *test5 = "";
    const char *test6 = "space ";
    
    printf("%s: %d\n", test1, is_ending_alphanumeric(test1));
    printf("%s: %d\n", test2, is_ending_alphanumeric(test2));
    printf("%s: %d\n", test3, is_ending_alphanumeric(test3));
    printf("%s: %d\n", test4, is_ending_alphanumeric(test4));
    printf("%s: %d\n", test5, is_ending_alphanumeric(test5));
    printf("%s: %d\n", test6, is_ending_alphanumeric(test6));
    
    return 0;
}