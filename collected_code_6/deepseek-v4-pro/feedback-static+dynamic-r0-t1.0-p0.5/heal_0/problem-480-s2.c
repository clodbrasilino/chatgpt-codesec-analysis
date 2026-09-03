#include <stdio.h>
#include <string.h>
#include <limits.h>

char max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    
    int count[UCHAR_MAX + 1] = {0};
    const unsigned char *s = (const unsigned char *)str;
    
    while (*s) {
        count[*s]++;
        s++;
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
    char str[1000];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    char result = max_occurring_char(str);
    
    if (result == '\0') {
        printf("Empty string\n");
    } else {
        printf("Maximum occurring character: %c\n", result);
    }
    
    return 0;
}