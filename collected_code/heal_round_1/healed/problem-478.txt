#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isLowercase(const char c) {
    return (c >= 'a' && c <= 'z');
}

void removeLowercaseSubstrings(char* str) {
    if(str == NULL)
        return;
    int len = strlen(str);
    int i = 0;
    while(i < len) {
        if(isLowercase(str[i])) {
            int j = i + 1;
            while(j < len && isLowercase(str[j])) {
                j++;
            }
            memmove(&str[i], &str[j], len - j + 1);
            len -= (j - i);
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "HeLLo WOrLd";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}