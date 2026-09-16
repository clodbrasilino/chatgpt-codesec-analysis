#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void remove_chars(char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return;
    }

    uint8_t hash[256] = {0};
    int i = 0;
    int destIndex = 0;

    while (str2[i] != '\0') {
        hash[(unsigned char)str2[i]] = 1;
        i++;
    }

    i = 0;
    while (str1[i] != '\0') {
        if (hash[(unsigned char)str1[i]] == 0) {
            str1[destIndex] = str1[i];
            destIndex++;
        }
        i++;
    }
    str1[destIndex] = '\0';
}

int main(void) {
    char str1[] = "hello world";
    const char *str2 = "ol";

    remove_chars(str1, str2);

    printf("%s\n", str1);

    return 0;
}