#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countSubstrings(const char* str) {
    if(str == NULL){
        return 0;
    }
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