#include <stdio.h>

void minimizeStringLength(char* str) {
    if (str == NULL) {
        return;
    }

    if (str[0] == '\0') {
        return;
    }

    int freq[256] = {0};
    int maxFreq = 0;
    char charToRemove = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
        if (freq[c] > maxFreq) {
            maxFreq = freq[c];
            charToRemove = str[i];
        }
    }

    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != charToRemove) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str1[] = "programming";
    minimizeStringLength(str1);
    printf("%s\n", str1);

    char str2[] = "hello world";
    minimizeStringLength(str2);
    printf("%s\n", str2);

    char str3[] = "a";
    minimizeStringLength(str3);
    printf("%s\n", str3);

    return 0;
}