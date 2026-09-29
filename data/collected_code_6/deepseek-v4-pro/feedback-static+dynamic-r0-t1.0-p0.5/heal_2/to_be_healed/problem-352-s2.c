#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return true;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char seen[256] = {0};
    
    for (size_t i = 0; str[i] != '\0'; i++) {
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