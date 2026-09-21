#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    int count[256] = {0};
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    int length = strnlen(str, 1048576);
    
    for (int i = 0; i < length; i++) {
        if (str[i] == '\0') {
            break;
        }
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