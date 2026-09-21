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
    char *input = NULL;
    size_t size = 0;

    if (getline(&input, &size, stdin) == -1) {
        free(input);
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        free(input);
        return 0;
    }

    if (len > 255) {
        free(input);
        return 1;
    }

    char buffer[256];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    free(input);

    int length = (int)strnlen(buffer, sizeof(buffer));
    if (length == 0) {
        return 0;
    }

    permute(buffer, 0, length - 1);

    return 0;
}