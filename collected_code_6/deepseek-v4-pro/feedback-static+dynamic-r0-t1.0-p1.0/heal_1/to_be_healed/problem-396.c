#include <stdio.h>
#include <string.h>
#include <regex.h>

int starts_and_ends_same(const char *str) {
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[128];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (len == 0) return 0;
    if (len == 1) return 1;
    
    snprintf(pattern, sizeof(pattern), "^%c.*%c$", str[0], str[len - 1]);
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) return 0;
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = "abca";
    const char *test6 = "abcab";
    
    printf("%s: %d\n", test1, starts_and_ends_same(test1));
    printf("%s: %d\n", test2, starts_and_ends_same(test2));
    printf("%s: %d\n", test3, starts_and_ends_same(test3));
    printf("%s: %d\n", test4, starts_and_ends_same(test4));
    printf("%s: %d\n", test5, starts_and_ends_same(test5));
    printf("%s: %d\n", test6, starts_and_ends_same(test6));
    
    return 0;
}