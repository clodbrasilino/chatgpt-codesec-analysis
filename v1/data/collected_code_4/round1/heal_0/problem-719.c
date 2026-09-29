#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool matchPattern(const char* str) {
    int len = strlen(str);
    bool foundA = false;
   
    for(int i = 0; i < len; i++) {
        if(i == len-1 && str[i] == 'a') {
            return false;
        }
        if(str[i] == 'a') {
            foundA = true;
        } else if(foundA && str[i] != 'b') {
            return false;
        }
    }
   
    return foundA;
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    scanf("%s", str);
    
    if(matchPattern(str)) {
        printf("Matches pattern\n");
    } else {
        printf("Doesn't match pattern\n");
    }
   
    return 0;
}