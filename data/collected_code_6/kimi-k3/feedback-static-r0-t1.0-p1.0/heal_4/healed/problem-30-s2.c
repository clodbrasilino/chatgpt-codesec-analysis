#include <stdio.h>
#include <string.h>

long long countSubstringsWithSameStartAndEnd(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    long long count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    const char *test1 = "abcab";
    const char *test2 = "aba";
    const char *test3 = "a";
    const char *test4 = "";
    
    printf("String: \"%s\" -> Count: %lld\n", test1, countSubstringsWithSameStartAndEnd(test1, strnlen(test1, 1024)));
    printf("String: \"%s\" -> Count: %lld\n", test2, countSubstringsWithSameStartAndEnd(test2, strnlen(test2, 1024)));
    printf("String: \"%s\" -> Count: %lld\n", test3, countSubstringsWithSameStartAndEnd(test3, strnlen(test3, 1024)));
    printf("String: \"%s\" -> Count: %lld\n", test4, countSubstringsWithSameStartAndEnd(test4, strnlen(test4, 1024)));
    
    return 0;
}