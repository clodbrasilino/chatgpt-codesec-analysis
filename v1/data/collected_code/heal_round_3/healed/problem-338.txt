#include <stdio.h>
#include <string.h>

int countSubstrings(const char* str, size_t maxlen) {
    int count = 0;
    if (!str) {
        return count;
    }
   
    int len = strnlen(str, maxlen);
   
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
    char str[] = "abbacd";
    int count = countSubstrings(str, sizeof(str)/sizeof(char) - 1);

    printf("Number of substrings with same first and last characters: %d\n", count);

    return 0;
}