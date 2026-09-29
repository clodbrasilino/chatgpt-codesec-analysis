#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_range(char *str, size_t left, size_t right) {
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_words(char *str, size_t length) {
    if (str == NULL || length == 0) {
        return;
    }

    reverse_range(str, 0, length - 1);

    size_t start = 0;
    for (size_t i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i > start) {
                reverse_range(str, start, i - 1);
            }
            start = i + 1;
        }
    }
}

int main(void) {
    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(buffer, buffer_size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    reverse_words(buffer, len);

    printf("%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}