#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = 0, i = strlen(s) - 1;
    while (i >= 0 && isspace(s[i])) i--;
    while (i >= 0 && !isspace(s[i])) {
        length++;
        i--;
    }
    return length;
}

int main() {
    const char *str = "Find the length of this    ";
    int last_word_length = lengthOfLastWord(str);
    printf("Length of the last word: %d\n", last_word_length);
    return 0;
}