#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_range(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }

    reverse_range(str, 0, len - 1);

    size_t word_start = 0;
    size_t i = 0;

    while (i <= len) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i > word_start) {
                reverse_range(str, word_start, i - 1);
            }
            word_start = i + 1;
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;

    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        return EXIT_FAILURE;
    }

    if (read > 0 && buffer[read - 1] == '\n') {
        buffer[read - 1] = '\0';
        read--;
    }

    reverse_words(buffer, (size_t)read);

    printf("%s\n", buffer);

    free(buffer);

    return EXIT_SUCCESS;
}