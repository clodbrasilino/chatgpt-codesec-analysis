#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLEN 100

void abbreviateRoad(char* str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);

    if (len <= 0 || len > MAX_STRLEN) {
        return;
    }

    char* temp = malloc(sizeof(char) * (MAX_STRLEN + 1));

    if (temp == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, str, len);
    temp[len] = '\0';

    char *start = strstr(temp, "road");
    if (start) {
        *start++ = 'r';
        *start++ = 'd';
        *start = '\0';
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t newLen = strlen(temp);

    if (newLen > MAX_STRLEN) {
        free(temp);
        return;
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(str, temp, newLen);
    str[newLen] = '\0';
    free(temp);
}

int main() {
    char* str = malloc(sizeof(char) * (MAX_STRLEN + 1));

    if (str == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Enter a string: ");
    if (fgets(str, MAX_STRLEN, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }

    abbreviateRoad(str);
    printf("Abbreviated string: %s\n", str);

    free(str);

    return 0;
}