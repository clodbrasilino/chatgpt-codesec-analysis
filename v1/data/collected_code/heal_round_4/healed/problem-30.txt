#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countSubstrings(const char* str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);

    if (len == 0 || len > 100){
        return 0;
    }
    
    int count = 0;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    char str[] = "ababa";
    int result = countSubstrings(str);
    printf("Number of substrings: %d\n", result);

    return 0;
}