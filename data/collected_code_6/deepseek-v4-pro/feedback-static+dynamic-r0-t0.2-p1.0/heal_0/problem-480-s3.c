#include <stdio.h>
#include <string.h>
#include <limits.h>

char findMaxOccurringChar(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    
    int count[UCHAR_MAX + 1] = {0};
    const unsigned char *s = (const unsigned char *)str;
    
    while (*s) {
        count[*s]++;
        s++;
    }
    
    char maxChar = str[0];
    int maxCount = 0;
    
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxChar = (char)i;
        }
    }
    
    return maxChar;
}

int main(void) {
    char str[1000];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    if (str[0] == '\0') {
        printf("Empty string\n");
        return 0;
    }
    
    char result = findMaxOccurringChar(str);
    printf("Maximum occurring character: %c\n", result);
    
    return 0;
}