#include <stdbool.h>
#include <stdio.h>

bool areAllCharactersUnique(const char* str) {
    int charCount[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        if (charCount[(unsigned char)str[i]] > 0) {
            return false;
        }
        charCount[(unsigned char)str[i]]++;
    }

    return true;
}

int main() {
    const char* str1 = "Hello, world!";
    const char* str2 = "abcdef";

    if (areAllCharactersUnique(str1))
        printf("All characters in str1 are unique\n");
    else
        printf("All characters in str1 are not unique\n");

    if (areAllCharactersUnique(str2))
        printf("All characters in str2 are unique\n");
    else
        printf("All characters in str2 are not unique\n");

    return 0;
}