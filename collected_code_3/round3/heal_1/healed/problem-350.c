#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 256

void removeChar(char* str, char c) {
    int j = 0;
    int n = strlen(str);
    for (int i = 0; i < n; i++)
        if (str[i] != c)
            str[j++] = str[i];
    str[j] = '\0';
}

char getMinLengthChar(char* str) {
    int count[MAX_CHAR] = {0};
    int min = INT_MAX;
    char res = '\0';
    int n = strlen(str);
    
    for (int i = 0; i < n; i++)
        count[(int)str[i]]++;
    
    for(int i = 0; i < n; i++) {
        if(min > count[(int)str[i]]) {
            min = count[(int)str[i]];
            res = str[i];
        }
    }

    return res;
}

void minimizeLength(char* str) {
    char minChar = getMinLengthChar(str);
    if(minChar != '\0')
        removeChar(str, minChar);
}

int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    minimizeLength(str);
    printf("Minimized string: %s\n", str);
    return 0;
}