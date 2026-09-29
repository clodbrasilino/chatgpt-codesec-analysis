#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int current_length = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\n' && s[i] != '\r') {
            current_length++;
            length = current_length;
        } else if (s[i] == ' ') {
            current_length = 0;
        }
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