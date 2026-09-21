#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_spaces(char *str, size_t len, char ch) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (i < len && str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = ch;
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&buffer, &len, stdin);
    if (read == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }

    size_t actual_len = (size_t)read;
    if (actual_len > 0) {
        if (buffer[actual_len - 1] == '\n') {
            buffer[actual_len - 1] = '\0';
            actual_len--;
        }
        if (actual_len > 0) {
            replace_spaces(buffer, actual_len, '_');
        }
    }

    if (buffer != NULL) {
        printf("%s\n", buffer);
    }

    free(buffer);
    return EXIT_SUCCESS;
}