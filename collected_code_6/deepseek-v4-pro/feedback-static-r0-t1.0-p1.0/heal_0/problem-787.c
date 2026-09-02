#include <stdio.h>
#include <string.h>

int match_abbb(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'a') {
            if (i + 3 < len && 
                str[i+1] == 'b' && 
                str[i+2] == 'b' && 
                str[i+3] == 'b') {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "ab";
    const char *test3 = "abbbb";
    const char *test4 = "aabb";
    const char *test5 = "bbb";
    const char *test6 = "xabbbx";
    
    printf("%s: %d\n", test1, match_abbb(test1));
    printf("%s: %d\n", test2, match_abbb(test2));
    printf("%s: %d\n", test3, match_abbb(test3));
    printf("%s: %d\n", test4, match_abbb(test4));
    printf("%s: %d\n", test5, match_abbb(test5));
    printf("%s: %d\n", test6, match_abbb(test6));
    
    return 0;
}