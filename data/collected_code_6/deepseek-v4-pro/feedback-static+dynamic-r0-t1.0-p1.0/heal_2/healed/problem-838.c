#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToEqual(char *s1, char *s2) {
    if (!s1 || !s2) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1000);
    size_t len2 = strnlen(s2, 1000);
    
    if (len1 != len2 || len1 == 1000) {
        return -1;
    }
    
    int len = (int)len1;
    int count1 = 0, count2 = 0;
    int diff1 = 0, diff2 = 0;
    
    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') diff1++;
            else diff2++;
        }
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    if (diff1 == 0 && diff2 == 0) {
        return 0;
    }
    
    if (diff1 % 2 == 1 || diff2 % 2 == 1) {
        return -1;
    }
    
    return (diff1 / 2) + (diff2 / 2) + (diff1 % 2) * 2;
}

int main(void) {
    char s1[1001], s2[1001];
    
    while (fgets(s1, sizeof(s1), stdin) && fgets(s2, sizeof(s2), stdin)) {
        s1[strcspn(s1, "\n")] = '\0';
        s2[strcspn(s2, "\n")] = '\0';
        
        int result = minSwapsToEqual(s1, s2);
        printf("%d\n", result);
    }
    
    return 0;
}