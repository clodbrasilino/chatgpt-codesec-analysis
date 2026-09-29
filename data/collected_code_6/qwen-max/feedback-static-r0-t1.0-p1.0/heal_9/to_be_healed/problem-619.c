#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* move_numbers(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *numStr = (char *)malloc(len + 1);
    if (numStr == NULL) {
        return NULL;
    }
    numStr[0] = '\0';
    int numIndex = 0;
    int nonNumCount = 0;

    for (size_t i = 0; i < len; ++i) {
        if (isdigit((unsigned char)str[i])) {
            numStr[numIndex++] = str[i];
        } else {
            str[nonNumCount++] = str[i];
        }
    }
    numStr[numIndex] = '\0';

    if (numIndex > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(&str[nonNumCount], numStr, numIndex);
        str[nonNumCount + numIndex] = '\0';
    }

    free(numStr);
    return str;
}

int main() {
    char str[] = "Hello123World456";
    char *result = move_numbers(str);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}