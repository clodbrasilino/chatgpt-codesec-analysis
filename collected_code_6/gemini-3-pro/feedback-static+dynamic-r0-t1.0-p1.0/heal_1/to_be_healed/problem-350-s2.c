#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void minStringLength(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        minStringLength(str);
        printf("%s\n", str);
    }

    return 0;
}