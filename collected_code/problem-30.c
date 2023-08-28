#include <stdio.h>
#include <string.h>

int countSubstrings(char* str) {
    int len = strlen(str);
    int count = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
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