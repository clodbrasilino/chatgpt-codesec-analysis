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
    int i = strlen(s) - 1;

    while (i >= 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\r')) {
        i--;
    }
    
    while (i >= 0 && s[i] != ' ' && s[i] != '\n' && s[i] != '\r') {
        length++;
        i--;
    }

    return length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[10000];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("%d\n", lengthOfLastWord(buffer));
    }

    return 0;
}