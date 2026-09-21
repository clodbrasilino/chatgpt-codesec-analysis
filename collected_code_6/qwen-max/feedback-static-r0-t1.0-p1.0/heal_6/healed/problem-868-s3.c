#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    const char *p = s;

    while (*p) {
        if (isspace((unsigned char)*p)) {
            if (len > 0) break;
        } else {
            len = 1;
        }
        p++;
    }

    while (*p) {
        if (isspace((unsigned char)*p)) {
            if (len > 0) break;
        } else if (len == 0) {
            len = 1;
        } else {
            len++;
        }
        p++;
    }

    return len;
}

int main() {
    const char *s = "Hello, World!";
    int result = lengthOfLastWord(s);
    printf("Length of last word: %d\n", result);
    return 0;
}