#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matchString(const char* str, size_t str_len) {
    if (str == NULL || str_len < 3) {
        return false;
    }

    for(size_t i = 0; i < str_len - 2; i++) {
        if(str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'b') {
            return true;
        }
    }

    return false;
}

int main() {
    const char str[] = "abb";
    size_t str_len = sizeof(str) / sizeof(str[0]) - 1;
    
    if(matchString(str, str_len)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }
    
    return 0;
}