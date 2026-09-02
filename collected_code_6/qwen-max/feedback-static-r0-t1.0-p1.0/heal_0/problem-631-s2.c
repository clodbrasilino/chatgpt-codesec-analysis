#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str) {
    regex_t space_regex, underscore_regex;
    char tmp[1024];
    
    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }
    
    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        snprintf(tmp, sizeof(tmp), "%s", regsub(&space_regex, str, "_"));
        strcpy(str, tmp);
    }
    
    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        snprintf(tmp, sizeof(tmp), "%s", regsub(&underscore_regex, str, " "));
        strcpy(str, tmp);
    }
    
    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    
    swap_spaces_underscores(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}