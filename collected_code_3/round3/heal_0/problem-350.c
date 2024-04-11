#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

void removeChar(char* str, char c) {
    int j = 0;
    int n = strlen(str);
    for (int i=0; i<n; i++)
        if (str[i] != c)
            str[j++] = str[i];
    str[j] = '\0';
}

char getMinLengthChar(char* str) {
    int count[MAX_CHAR] = {0};
    int min = MAX_CHAR;
    char res;
    int n = strlen(str);
    for (int i = 0; i < n; i++)
        count[str[i]]++;
    for (int i = 0; i < n; i++) {
        if (min > count[str[i]]) {
            min = count[str[i]];
            res = str[i];
        }
    }
    return res;
}

void minimizeLength(char* str) {
    char minChar = getMinLengthChar(str);
    removeChar(str, minChar);
}

int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    minimizeLength(str);
    printf("Minimized string: %s\n", str);
    return 0;
}