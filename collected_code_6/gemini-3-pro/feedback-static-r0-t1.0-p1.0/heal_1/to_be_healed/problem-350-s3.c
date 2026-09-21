#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minimizeString(const char *str, char *result) {
    if (str == NULL || result == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) {
        result[0] = '\0';
        return;
    }

    int maxCount = 0;
    char charToRemove = '\0';
    int counts[256] = {0};

    for (int i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > maxCount) {
            maxCount = counts[c];
            charToRemove = c;
        }
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != charToRemove) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
}

int main(void) {
    const char *original = "abracadabra";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(original);
    
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return 1;
    }

    minimizeString(original, result);
    printf("%s\n", result);

    free(result);
    return 0;
}