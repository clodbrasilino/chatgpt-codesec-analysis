#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

long long count_substrings(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    size_t n = strlen(s);
    long long count = 0;
    
    for (size_t i = 0; i < n; i++) {
        int sum = 0;
        for (size_t j = i; j < n; j++) {
            if (!isdigit((unsigned char)s[j])) {
                break;
            }
            sum += s[j] - '0';
            if (sum == (int)(j - i + 1)) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    const char *test1 = "123456";
    const char *test2 = "112";
    const char *test3 = "123";
    
    printf("Test 1: %lld\n", count_substrings(test1));
    printf("Test 2: %lld\n", count_substrings(test2));
    printf("Test 3: %lld\n", count_substrings(test3));
    
    return 0;
}