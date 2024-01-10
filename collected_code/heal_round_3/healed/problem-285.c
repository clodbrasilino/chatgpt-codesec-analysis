#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matchString(const char* str) {
    if (str == NULL) {
        return false;
    }

    size_t length = strlen(str);
    if(length < 3) {
        return false;
    }

    for(size_t i = 0; i < length - 2; i++) {
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