#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areCharactersUnique(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);
    if (length > 256) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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