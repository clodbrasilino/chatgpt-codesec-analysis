#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    unsigned char seen[256] = {0};
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = 1;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";
    
    printf("%s: %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    printf("%s: %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    printf("%s: %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    printf("%s: %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    
    return 0;
}