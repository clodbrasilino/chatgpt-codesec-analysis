#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool can_rearrange(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    
    if (len > 1024) {
        return false;
    }
    
    if (len == 0) {
        return true;
    }
    
    int char_count[256] = {0};
    int max_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        char_count[(unsigned char)str[i]]++;
        if (char_count[(unsigned char)str[i]] > max_count) {
            max_count = char_count[(unsigned char)str[i]];
        }
    }
    
    return max_count <= (int)((len + 1) / 2);
}

int main(void) {
    const char str1[] = "aaabb";
    const char str2[] = "aaaa";
    const char str3[] = "abcabc";
    const char str4[] = "";
    const char str5[] = "a";
    const char str6[] = "ab";
    const char str7[] = "aabbcc";
    
    printf("%s: %s\n", str1, can_rearrange(str1) ? "true" : "false");
    printf("%s: %s\n", str2, can_rearrange(str2) ? "true" : "false");
    printf("%s: %s\n", str3, can_rearrange(str3) ? "true" : "false");
    printf("\"\": %s\n", can_rearrange(str4) ? "true" : "false");
    printf("%s: %s\n", str5, can_rearrange(str5) ? "true" : "false");
    printf("%s: %s\n", str6, can_rearrange(str6) ? "true" : "false");
    printf("%s: %s\n", str7, can_rearrange(str7) ? "true" : "false");
    
    return 0;
}