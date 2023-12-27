#include <stdio.h>
#include <string.h>

int countSubstrings(const char* str) {
    int count = 0;
    int len = str ? strlen(str) : 0;

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
    int count = countSubstrings(str ? str : "");

    printf("Number of substrings with same first and last characters: %d\n", count);

    return 0;
}