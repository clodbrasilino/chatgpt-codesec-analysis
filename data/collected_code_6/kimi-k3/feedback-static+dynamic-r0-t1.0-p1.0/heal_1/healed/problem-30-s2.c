#include <stdio.h>
#include <string.h>

long long countSubstringsWithSameStartAndEnd(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
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
    
    printf("String: \"%s\" -> Count: %lld\n", test1, countSubstringsWithSameStartAndEnd(test1));
    printf("String: \"%s\" -> Count: %lld\n", test2, countSubstringsWithSameStartAndEnd(test2));
    printf("String: \"%s\" -> Count: %lld\n", test3, countSubstringsWithSameStartAndEnd(test3));
    printf("String: \"%s\" -> Count: %lld\n", test4, countSubstringsWithSameStartAndEnd(test4));
    
    return 0;
}