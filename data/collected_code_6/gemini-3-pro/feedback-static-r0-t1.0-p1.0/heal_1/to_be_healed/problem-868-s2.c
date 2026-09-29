#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s);
    int i = n - 1;

    while (i >= 0 && s[i] == ' ') {
        i--;
    }

    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }

    return length;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    
    printf("%d\n", lengthOfLastWord(test1));
    printf("%d\n", lengthOfLastWord(test2));
    printf("%d\n", lengthOfLastWord(test3));
    
    return 0;
}