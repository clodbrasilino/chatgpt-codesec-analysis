#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_chars(char *str1, const char *str2) {
    int hash[256] = {0};
    int i, index;
    for (i = 0; str2[i]; i++) {
        hash[(unsigned char)str2[i]] = 1;
    }
    i = 0;
    while (str1[i]) {
        if (hash[(unsigned char)str1[i]]) {
            for (index = i; str1[index]; index++) {
                str1[index] = str1[index + 1];
            }
            i--;
        }
        i++;
    }
}

int main() {
    char str1[] = "hello world";
    const char *str2 = "lo";
    printf("Original: %s\n", str1);
    remove_chars(str1, str2);
    printf("Modified: %s\n", str1);
    return 0;
}