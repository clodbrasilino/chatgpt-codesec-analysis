#include <stdio.h>
#include <string.h>
#include <limits.h>

char most_common_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    
    int count[UCHAR_MAX + 1] = {0};
    const unsigned char *u_str = (const unsigned char *)str;
    
    while (*u_str) {
        count[*u_str]++;
        u_str++;
    }
    
    int max_count = 0;
    char max_char = '\0';
    
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }
    
    return max_char;
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "aabbbcccc";
    char str3[] = "";
    const char *str4 = NULL;
    
    printf("Most common in '%s': '%c'\n", str1, most_common_char(str1));
    printf("Most common in '%s': '%c'\n", str2, most_common_char(str2));
    printf("Most common in '%s': '%c'\n", str3, most_common_char(str3));
    printf("Most common in NULL: '%c'\n", most_common_char(str4));
    
    return 0;
}