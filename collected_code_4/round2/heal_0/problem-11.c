#include <stdio.h>
#include <string.h>

char *removeOccurences(char *str, char c) {
    int firstIdx = -1;
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] == c) {
            if(firstIdx == -1) {
                firstIdx = i;
            } else {
                str[i] = '\0';
            }
        }
    }
    if (firstIdx != -1) {
        str[firstIdx] = '\0';
    }

    return str;
}

int main() {
    char str[100] = "Hello World Example Sentence";
    char c = 'e';
    printf("Original String: %s\n", str);
    char *modifiedStr = removeOccurences(str, c);
    printf("Modified String: %s\n", modifiedStr);

    return 0;
}