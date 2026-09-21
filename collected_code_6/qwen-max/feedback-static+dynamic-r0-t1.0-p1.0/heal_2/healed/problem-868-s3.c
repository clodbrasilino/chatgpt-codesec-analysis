#include <stdio.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    int i = 0;

    while (s[i] != '\0') {
        if (isspace(s[i])) {
            len = 0;
        } else {
            len++;
        }
        i++;
    }

    return len;
}

int main() {
    const char *s = "Hello, World!";
    int result = lengthOfLastWord(s);
    printf("Length of last word: %d\n", result);
    return 0;
}