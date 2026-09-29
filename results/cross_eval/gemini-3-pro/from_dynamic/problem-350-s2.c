#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void minStringLength(char *str) {
    if (str == NULL) {
        return;
    }

    int n = strlen(str);
    if (n == 0) {
        return;
    }

    int freq[256] = {0};
    int maxFreq = 0;
    char charToRemove = '\0';

    for (int i = 0; i < n; i++) {
        freq[(unsigned char)str[i]]++;
        if (freq[(unsigned char)str[i]] > maxFreq) {
            maxFreq = freq[(unsigned char)str[i]];
            charToRemove = str[i];
        }
    }

    int dest = 0;
    for (int src = 0; src < n; src++) {
        if (str[src] != charToRemove) {
            str[dest++] = str[src];
        }
    }
    str[dest] = '\0';
}

int main(void) {
    char str[256];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        minStringLength(str);
        printf("%s\n", str);
    }

    return 0;
}