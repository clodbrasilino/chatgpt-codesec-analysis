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
    char buffer[256] = {0};
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return 0;
    }

    if (len > 255) {
        return 1;
    }

    int length = (int)strnlen(buffer, sizeof(buffer));
    if (length == 0) {
        return 0;
    }

    permute(buffer, 0, length - 1);

    return 0;
}