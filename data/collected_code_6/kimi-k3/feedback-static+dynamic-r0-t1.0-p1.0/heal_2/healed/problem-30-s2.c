#include <stdio.h>
#include <string.h>
#include <stddef.h>

long long countSubstringsWithSameStartAndEnd(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len && max_len > 0 && str[len - 1] != '\0') {
        return -1;
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
    
    printf("String: \"%s\" -> Count: %lld\n", test1, countSubstringsWithSameStartAndEnd(test1, strlen(test1) + 1));
    printf("String: \"%s\" -> Count: %lld\n", test2, countSubstringsWithSameStartAndEnd(test2, strlen(test2) + 1));
    printf("String: \"%s\" -> Count: %lld\n", test3, countSubstringsWithSameStartAndEnd(test3, strlen(test3) + 1));
    printf("String: \"%s\" -> Count: %lld\n", test4, countSubstringsWithSameStartAndEnd(test4, 1));
    
    return 0;
}