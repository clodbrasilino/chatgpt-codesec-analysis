#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int lengthOfLastWord(const char *s, size_t len) {
    if (s == NULL || len == 0) {
        return 0;
    }

    int length = 0;
    int i = (int)len - 1;

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
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;

    while ((chars_read = getline(&buffer, &bufsize, stdin)) != -1) {
        printf("%d\n", lengthOfLastWord(buffer, (size_t)chars_read));
    }

    free(buffer);
    return 0;
}