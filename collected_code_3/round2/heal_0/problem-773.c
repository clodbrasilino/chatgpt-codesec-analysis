#include <stdio.h>
#include <string.h>

void findSubstring(char* str, char* subStr) {
    int len = strlen(str);
    int subLen = strlen(subStr);
    for(int i = 0; i <= len - subLen; i++) {
        int j;
        for(j = 0; j < subLen; j++) {
            if(str[i + j] != subStr[j]) {
                break;
            }
        }
        if(j == subLen) {
            printf("Substring found at position %d\n", i + 1);
        }
    }
}

int main() {
    char str[100], subStr[50];
    printf("Enter a string: ");
    gets(str);
    printf("Enter a substring to find: ");
    gets(subStr);
    findSubstring(str, subStr);
    return 0;
}