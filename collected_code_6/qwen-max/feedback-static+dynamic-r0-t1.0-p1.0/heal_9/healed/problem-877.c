#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str) {
    size_t len = strnlen(str, 1024);
    if (len >= 1024 && str[len - 1] != '\0') {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        exit(1);
    }
    char *temp = malloc(len + 1);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(temp, str, len);
    temp[len] = '\0';

    for (size_t i = 0; i < len - 1; ++i) {
        for (size_t j = i + 1; j < len; ++j) {
            if (temp[i] > temp[j]) {
                char c = temp[i];
                temp[i] = temp[j];
                temp[j] = c;
            }
        }
    }

    strncpy(str, temp, len);
    str[len] = '\0';
    free(temp);
}

int main() {
    char str[] = "programming";
    printf("Original string: %s\n", str);
    sort_string(str);
    printf("Sorted string: %s\n", str);
    return 0;
}