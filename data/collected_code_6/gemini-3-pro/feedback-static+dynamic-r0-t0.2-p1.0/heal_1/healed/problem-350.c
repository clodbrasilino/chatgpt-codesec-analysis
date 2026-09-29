#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minimizeString(char *str) {
    if (str == NULL) {
        return;
    }

    int freq[256] = {0};
    int len = 0;
    
    while (str[len] != '\0') {
        freq[(unsigned char)str[len]]++;
        len++;
    }

    if (len == 0) {
        return;
    }

    int maxFreq = 0;
    char charToRemove = '\0';
    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            charToRemove = (char)i;
        }
    }

    if (maxFreq == 0) {
        return;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != charToRemove) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char *str = malloc(1024 * sizeof(char));
    if (str == NULL) {
        return 1;
    }

    if (fgets(str, 1024, stdin) != NULL) {
        char *newline = strchr(str, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        minimizeString(str);
        printf("%s\n", str);
    }

    free(str);
    return 0;
}