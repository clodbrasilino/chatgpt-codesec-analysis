#include <stdio.h>
#include <string.h>

int countSubstrings(char* str) {
    int substrCounts[26] = {0};
    int strLength = strlen(str);
    
    for(int i = 0; i < strLength; i++) {
        substrCounts[str[i] - 'a']++;
    }

    int total = 0;
    for(int i = 0; i < 26; i++) {
        total += ((substrCounts[i] * (substrCounts[i] + 1)) / 2);
    }

    return total;
}

int main() {
    char str[] = "abcab";
    printf("Count of substrings: %d\n", countSubstrings(str));
    return 0;
}