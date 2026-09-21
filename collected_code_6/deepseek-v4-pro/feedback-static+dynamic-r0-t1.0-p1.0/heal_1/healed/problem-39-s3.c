#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

bool canRearrange(const char *str) {
    int len = 0;
    int count[ALPHABET_SIZE] = {0};
    int max_count = 0;
    
    if (str == NULL) {
        return false;
    }
    
    while (str[len] != '\0') {
        if (str[len] >= 'a' && str[len] <= 'z') {
            count[str[len] - 'a']++;
            if (count[str[len] - 'a'] > max_count) {
                max_count = count[str[len] - 'a'];
            }
        } else if (str[len] >= 'A' && str[len] <= 'Z') {
            count[str[len] - 'A']++;
            if (count[str[len] - 'A'] > max_count) {
                max_count = count[str[len] - 'A'];
            }
        }
        len++;
    }
    
    if (len == 0) {
        return true;
    }
    
    return max_count <= (len + 1) / 2;
}

int main(void) {
    char str1[] = "aab";
    char str2[] = "aaab";
    char str3[] = "aabbcc";
    char str4[] = "aaaabc";
    char str5[] = "";
    
    printf("%s: %s\n", str1, canRearrange(str1) ? "Yes" : "No");
    printf("%s: %s\n", str2, canRearrange(str2) ? "Yes" : "No");
    printf("%s: %s\n", str3, canRearrange(str3) ? "Yes" : "No");
    printf("%s: %s\n", str4, canRearrange(str4) ? "Yes" : "No");
    printf("%s: %s\n", str5, canRearrange(str5) ? "Yes" : "No");
    
    return 0;
}