#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* move_numbers(char *str) {
    if (str == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *numStr = (char *)malloc(len + 1);
    if (numStr == NULL) return NULL;
    numStr[0] = '\0';

    char *nonNumStr = (char *)malloc(len + 1);
    if (nonNumStr == NULL) {
        free(numStr);
        return NULL;
    }
    nonNumStr[0] = '\0';

    int numLen = 0, nonNumLen = 0;
    for (size_t i = 0; i < len; ++i) {
        if (isdigit((unsigned char)str[i])) {
            numStr[numLen++] = str[i];
        } else {
            nonNumStr[nonNumLen++] = str[i];
        }
    }
    numStr[numLen] = '\0';
    nonNumStr[nonNumLen] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, nonNumStr);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(str, numStr);

    free(numStr);
    free(nonNumStr);
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