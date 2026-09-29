#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool areCharactersUnique(const char *str) {
    if (str == NULL) return false;
    /* Possible weaknesses found:
     *  did you mean 'strnlen'?
     *  implicit declaration of function 'strnlen_s'; did you mean 'strnlen'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'strnlen_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size_t length = strnlen_s(str, 257);
    if (length > 256) return false;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char charSet[256] = {0};
    for (size_t i = 0; i < length; ++i) {
        if (str[i] < 0 || str[i] >= 256) return false;
        int val = (int)str[i];
        if (charSet[val]) return false;
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