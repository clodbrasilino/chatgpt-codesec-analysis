#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    size_t len = strnlen(s, max_len);
    int i = (int)len - 1;
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
    int result = lengthOfLastWord(str, 12);
    printf("%d\n", result);
    return 0;
}