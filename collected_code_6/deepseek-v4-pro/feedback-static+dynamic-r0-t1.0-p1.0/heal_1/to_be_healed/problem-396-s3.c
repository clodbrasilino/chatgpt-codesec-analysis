#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int check_same_first_last(const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     *  Unused variable: pattern [unusedVariable]
     */
    char pattern[64];
    
    ret = regcomp(&regex, "^(.).*\\1$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "abca";
    const char *test5 = "";
    
    printf("%s: %d\n", test1, check_same_first_last(test1));
    printf("%s: %d\n", test2, check_same_first_last(test2));
    printf("%s: %d\n", test3, check_same_first_last(test3));
    printf("%s: %d\n", test4, check_same_first_last(test4));
    printf("%s: %d\n", test5, check_same_first_last(test5));
    
    return 0;
}