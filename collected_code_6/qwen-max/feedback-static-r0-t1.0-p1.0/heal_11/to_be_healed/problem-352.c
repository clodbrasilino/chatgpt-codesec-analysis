#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areCharactersUnique(const char *str, size_t strLen) {
    if (strLen > 256) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char charSet[256] = {0};
    for (size_t i = 0; i < strLen; ++i) {
        if ((unsigned char)str[i] >= 256) {
            return false;
        }
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

    size_t len1 = strnlen(test1, 256);
    size_t len2 = strnlen(test2, 256);

    printf("%s: %s\n", test1, areCharactersUnique(test1, len1) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2, areCharactersUnique(test2, len2) ? "Unique" : "Not Unique");

    return 0;
}