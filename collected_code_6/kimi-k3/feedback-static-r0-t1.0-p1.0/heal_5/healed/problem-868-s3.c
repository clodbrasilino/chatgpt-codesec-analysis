#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = max_len;

    if (s == NULL || i == 0) {
        return 0;
    }

    if (i > strlen(s)) {
        i = strlen(s);
    }

    while (i > 0 && s[i - 1] == ' ') {
        i--;
    }

    while (i > 0 && s[i - 1] != ' ') {
        len++;
        i--;
    }

    return len;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t read;

    errno = 0;
    read = getline(&str, &size, stdin);
    if (read == -1) {
        if (errno != 0) {
            perror("getline");
        }
        free(str);
        return 1;
    }

    if (read > 0 && str[read - 1] == '\n') {
        str[read - 1] = '\0';
        read--;
    }

    if (read > 0) {
        printf("%d\n", lengthOfLastWord(str, (size_t)read));
    } else {
        printf("0\n");
    }

    free(str);
    return 0;
}