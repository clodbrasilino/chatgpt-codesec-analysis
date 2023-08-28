#include <stdio.h>

int matchString(char* str) {
    int i = 0;
    
    while(str[i] != '\0') {
        if(str[i] == 'a') {
            if(str[i + 1] == 'b' && (str[i + 2] == 'b' || str[i + 2] == '\0')) {
                return 1;
            }
        }
        i++;
    }
    
    return 0;
}

int main() {
    char str[] = "abb";
    
    if(matchString(str)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}