#include <stdio.h>
#include <stdlib.h>

void minimizeString(char *str) {
    if (str == NULL) {
        return;
    }

    int freq[256] = {0};
    int i = 0;
    while (str[i] != '\0') {
        freq[(unsigned char)str[i]]++;
        i++;
    }

    int maxFreq = 0;
    char charToRemove = '\0';
    for (int k = 0; k < 256; k++) {
        if (freq[k] > maxFreq) {
            maxFreq = freq[k];
            charToRemove = (char)k;
        }
    }

    if (maxFreq == 0) {
        return;
    }

    int j = 0;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] != charToRemove) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main(void) {
    char *str = malloc(1024 * sizeof(char));
    if (str == NULL) {
        return 1;
    }

    if (fgets(str, 1024, stdin) != NULL) {
        size_t len = 0;
        while (len < 1024 && str[len] != '\0') {
            len++;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        minimizeString(str);
        printf("%s\n", str);
    }

    free(str);
    return 0;
}