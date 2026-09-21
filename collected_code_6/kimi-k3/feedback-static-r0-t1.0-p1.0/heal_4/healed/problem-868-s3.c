#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = max_len;

    if (i == 0) {
        return 0;
    }
    i--;

    while (i > 0 && s[i] == ' ') {
        i--;
    }

    while (i > 0 && s[i] != ' ') {
        len++;
        i--;
    }

    if (i == 0 && s[i] != ' ') {
        len++;
    }

    return len;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t read;

    read = getline(&str, &size, stdin);
    if (read == -1) {
        free(str);
        return 1;
    }

    if (read > 0 && str[read - 1] == '\n') {
        str[read - 1] = '\0';
        read--;
    }

    printf("%d\n", lengthOfLastWord(str, (size_t)read));
    free(str);

    return 0;
}