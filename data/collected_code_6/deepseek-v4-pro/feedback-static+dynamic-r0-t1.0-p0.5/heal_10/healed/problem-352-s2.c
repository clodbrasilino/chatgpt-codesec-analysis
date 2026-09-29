#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    size_t length = 0;
    while (length < 256 && str[length] != '\0') {
        length++;
    }
    
    if (length > 256 || (length == 256 && str[255] != '\0')) {
        return false;
    }
    
    unsigned char seen[256] = {0};
    
    for (size_t i = 0; i < length; i++) {
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
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, all_unique_chars(test1) ? "unique" : "not unique");
    printf("%s: %s\n", test2, all_unique_chars(test2) ? "unique" : "not unique");
    printf("%s: %s\n", test3, all_unique_chars(test3) ? "unique" : "not unique");
    printf("%s: %s\n", test4, all_unique_chars(test4) ? "unique" : "not unique");
    
    bool null_result = all_unique_chars(test5);
    printf("NULL: %s\n", null_result ? "unique" : "not unique");
    
    return 0;
}