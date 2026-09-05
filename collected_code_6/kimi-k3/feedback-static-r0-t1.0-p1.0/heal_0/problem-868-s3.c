#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s) {
    int len = 0;
    int i = (int)strlen(s) - 1;

    while (i >= 0 && s[i] == ' ') {
        i--;
    }

    while (i >= 0 && s[i] != ' ') {
        len++;
        i--;
    }

    return len;
}

int main(void) {
    char str[1024];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
        printf("%d\n", lengthOfLastWord(str));
    }

    return 0;
}