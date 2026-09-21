#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const char *end = s + strlen(s);
    const char *p = end - 1;

    while (p >= s && isspace((unsigned char)*p)) {
        p--;
    }

    while (p >= s && !isspace((unsigned char)*p)) {
        len++;
        p--;
    }

    return len;
}

int main() {
    const char *s = "Hello, World!";
    int result = lengthOfLastWord(s);
    printf("Length of last word: %d\n", result);
    return 0;
}