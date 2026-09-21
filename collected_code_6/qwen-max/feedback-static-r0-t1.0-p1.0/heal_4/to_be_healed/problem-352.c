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
        if (str[i] < 0 || str[i] > 255) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(test1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(test2);

    printf("%s: %s\n", test1, areCharactersUnique(test1, len1) ? "Unique" : "Not Unique");
    printf("%s: %s\n", test2, areCharactersUnique(test2, len2) ? "Unique" : "Not Unique");

    return 0;
}