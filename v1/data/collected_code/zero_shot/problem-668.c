#include <stdio.h>

void replaceMultipleOccurrences(char* str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    int len = 0;
    int i, j;
    
    while (str[len] != '\0') {
        len++;
    }
    
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                int k;
                for (k = j; k < len; k++) {
                    str[k] = str[k + 1];
                }
                len--;
                j--;
            }
        }
    }
}

int main() {
    char str[] = "abbccddeeff";
    
    replaceMultipleOccurrences(str);
    
    printf("%s\n", str);
    
    return 0;
}