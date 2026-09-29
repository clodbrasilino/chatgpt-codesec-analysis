#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countSubstrs(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int result = 0;
    int count[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char index = (unsigned char)str[i];
        count[index]++;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            result += (count[i] * (count[i] + 1)) / 2;
        }
    }

    return result;
}

int main(void) {
    const char *testStr = "abcab";
    int result = countSubstrs(testStr);
    
    printf("%d\n", result);
    
    return 0;
}