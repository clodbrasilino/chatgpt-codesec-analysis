#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;
    int result;
    
    ret = regcomp(&regex, "^abb\\{2,3\\}$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        result = 0;
    }
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "abb",
        "abbb",
        "abbbb",
        "a",
        "ab",
        "abbbb",
        "acbb",
        "abbbbb",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("%s: %s\n", test_strings[i], 
               match_pattern(test_strings[i]) ? "Match" : "No match");
    }
    
    return 0;
}