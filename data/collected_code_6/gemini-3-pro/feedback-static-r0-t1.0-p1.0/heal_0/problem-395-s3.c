#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char findFirstNonRepeatedChar(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int charCount[256] = {0};
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        charCount[(unsigned char)str[i]]++;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (charCount[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

int main(void) {
    const char *testStr = "swiss";
    char result = findFirstNonRepeatedChar(testStr);

    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found.\n");
    }

    return 0;
}