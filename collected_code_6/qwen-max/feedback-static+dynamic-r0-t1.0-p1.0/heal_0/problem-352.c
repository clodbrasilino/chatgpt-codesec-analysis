#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areCharactersUnique(const char *str) {
    int length = strlen(str);
    if (length > 256) {
        return false;
    }
    unsigned char charSet[256] = {0};
    for (int i = 0; i < length; ++i) {
        int val = (int)str[i];
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
    printf("%s: %s\n", test1, areCharactersUnique(test1) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2, areCharactersUnique(test2) ? "Unique" : "Not Unique");
    return 0;
}