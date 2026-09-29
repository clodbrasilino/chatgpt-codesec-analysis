#include <regex.h>
#include <stdbool.h>
#include <stddef.h>

bool startsAndEndsWithSameChar(const char* str) {
    regex_t regex;
    
    if (regcomp(&regex, "^([a-zA-Z]).*\\1$", REG_EXTENDED) != 0) {
        return false;
    }
    
    int result = regexec(&regex, str, 0, NULL, 0);
    
    regfree(&regex);
    
    return result == 0;
}

int main() {
    char testString[] = "abca";
    if(startsAndEndsWithSameChar(testString)) {
        return 1;
    }
    return 0;
}