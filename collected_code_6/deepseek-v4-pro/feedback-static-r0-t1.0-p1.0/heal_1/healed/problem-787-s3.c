#include <stdio.h>
#include <stdbool.h>

bool match_abbb(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    const char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == 'a' && 
            *(ptr + 1) == 'b' && 
            *(ptr + 2) == 'b' && 
            *(ptr + 3) == 'b') {
            return true;
        }
        ptr++;
    }
    
    return false;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "xabbbc";
    const char *test3 = "abb";
    const char *test4 = "abbbb";
    const char *test5 = "bbba";
    const char *test6 = "aabbb";
    const char *test7 = NULL;
    
    printf("Test '%s': %d\n", test1, match_abbb(test1));
    printf("Test '%s': %d\n", test2, match_abbb(test2));
    printf("Test '%s': %d\n", test3, match_abbb(test3));
    printf("Test '%s': %d\n", test4, match_abbb(test4));
    printf("Test '%s': %d\n", test5, match_abbb(test5));
    printf("Test '%s': %d\n", test6, match_abbb(test6));
    printf("Test NULL: %d\n", match_abbb(test7));
    
    return 0;
}