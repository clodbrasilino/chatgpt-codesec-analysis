#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    int count[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);
    int result = 0;

    for (int i = 0; i < length; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            result += count[i] * (count[i] + 1) / 2;
        }
    }

    return result;
}

int main(void) {
    const char *test1 = "abcab";
    const char *test2 = "aba";
    const char *test3 = "aaaa";

    printf("Test 1: %d\n", countSubstrings(test1));
    printf("Test 2: %d\n", countSubstrings(test2));
    printf("Test 3: %d\n", countSubstrings(test3));

    return 0;
}