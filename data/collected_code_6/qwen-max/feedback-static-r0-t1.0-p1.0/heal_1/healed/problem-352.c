#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areCharactersUnique(const char *str, size_t strLen) {
    if (strLen > 256) {
        return false;
    }
    unsigned char charSet[256] = {0};
    for (size_t i = 0; i < strLen; ++i) {
        unsigned char val = (unsigned char)str[i];
        if (charSet[val]) {
            return false;
        }
        charSet[val] = 1;
    }
    return true;
}

int main() {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    printf("%s: %s\n", test1, areCharactersUnique(test1, strlen(test1)) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2, areCharactersUnique(test2, strlen(test2)) ? "Unique" : "Not Unique");
    return 0;
}