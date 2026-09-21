#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minimizeString(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) {
        return;
    }

    int freq[256] = {0};
    for (int i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
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

int main() {
    char *str = malloc(1024 * sizeof(char));
    if (str == NULL) {
        return 1;
    }

    if (fgets(str, 1024, stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        minimizeString(str);
        printf("%s\n", str);
    }

    free(str);
    return 0;
}