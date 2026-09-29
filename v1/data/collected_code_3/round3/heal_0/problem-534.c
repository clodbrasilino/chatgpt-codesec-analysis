#include <stdio.h>
#include <string.h>

int findSubstring(char* string, char* sub) {
    int stringLen = strlen(string);
    int subLen = strlen(sub);
    for(int i = 0; i <= stringLen - subLen; i++) {
        int j;
        for(j = 0; j < subLen; j++) {
            if(string[i + j] != sub[j]) {
                break;
            }
        }
        if(j == subLen) {
            return i;
        }
    }
    return -1;
}

int main() {
    char string[100], sub[100];
    printf("Enter a string: ");
    gets(string);
    printf("Enter a substring to search: ");
    gets(sub);
    int location = findSubstring(string, sub);
    if(location != -1) {
        printf("Substring found at location: %d\n", location);
    } else {
        printf("Substring not found in the string.\n");
    }
    return 0;
}