#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    int i = strlen(s) - 1;

    while (i >= 0 && isspace(s[i])) {
        i--;
    }

    while (i >= 0 && !isspace(s[i])) {
        len++;
        i--;
    }

    return len;
}

int main() {
    const char *s = "Hello, World!";
    int result = lengthOfLastWord(s);
    printf("Length of last word: %d\n", result);
    return 0;
}