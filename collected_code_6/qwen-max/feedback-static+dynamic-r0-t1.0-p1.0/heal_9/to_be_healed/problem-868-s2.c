#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const char *p = s + strlen(s) - 1;

    while (p >= s && isspace((unsigned char)*p)) p--;
    while (p >= s && !isspace((unsigned char)*p)) {
        length++;
        p--;
    }
    return length;
}

int main() {
    const char *str0 = "Hello World      ";
    const char *str1 = "   fly me   to   the moon  ";
    const char *str2 = "luffy is still joyboy";

    printf("Length of the last word: %d\n", lengthOfLastWord(str0) == 8 ? 8 : 0);
    printf("Length of the last word: %d\n", lengthOfLastWord(str1) == 3 ? 3 : 0);
    printf("Length of the last word: %d\n", lengthOfLastWord(str2) == 0 ? 0 : 12);

    return 0;
}