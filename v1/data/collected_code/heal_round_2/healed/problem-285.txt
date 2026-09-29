#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matchString(const char* str) {
    if (str == NULL) {
        return false;
    }

    int length = strlen(str);
    for(int i = 0; i < length - 2; i++) {
        if(str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'b') {
            return true;
        }
    }

    return false;
}

int main() {
    const char str[] = "abb";
    
    if(matchString(str)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}