#include <stdio.h>
#include <string.h>
#include <regex.h>

int check_regex(const char *str) {
    regex_t reg;
    
    if (regcomp(&reg, "^[a-z]*_[a-z]*$", REG_EXTENDED) != 0)  {
        printf("Regex compilation failure. Exiting...\n");
        return -1;
    }
    
    int result = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    
    return result;
}

int main() {
    char *str = "apples_and_oranges";
    
    int result = check_regex(str);
    if (result == 0) {
        printf("Passed regex check, string valid.\n");
    } else if (result == REG_NOMATCH) {
        printf("Failed regex check, string invalid.\n");
    } else {
        printf("Failed to execute regex check.\n");
    }

    return 0;
}