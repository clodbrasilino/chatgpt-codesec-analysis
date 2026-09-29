#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t buffer_size) {
    size_t len = strnlen(s, buffer_size);
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
    size_t buffer_size = sizeof("Hello World");
    int result = lengthOfLastWord(str, buffer_size);
    printf("%d\n", result);
    return 0;
}