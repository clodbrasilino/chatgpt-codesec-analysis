#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t len;

    len = getline(&buffer, &bufsize, stdin);
    if (len == -1) {
        free(buffer);
        return 1;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        free(buffer);
        return 0;
    }

    if (len > 255) {
        free(buffer);
        return 1;
    }

    int length = (int)len;
    permute(buffer, 0, length - 1);

    free(buffer);
    return 0;
}