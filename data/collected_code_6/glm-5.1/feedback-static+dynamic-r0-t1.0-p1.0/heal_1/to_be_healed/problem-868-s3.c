#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s);
    int i = len - 1;
    int count = 0;

    while (i >= 0 && s[i] == ' ') {
        i--;
    }

    while (i >= 0 && s[i] != ' ') {
        count++;
        i--;
    }

    return count;
}

int main(int argc, char *argv[]) {
    const char *str = "Hello World";
    int result = lengthOfLastWord(str);
    printf("%d\n", result);
    return 0;
}