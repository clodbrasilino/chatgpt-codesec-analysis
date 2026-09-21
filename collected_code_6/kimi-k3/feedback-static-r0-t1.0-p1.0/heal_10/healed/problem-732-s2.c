#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t i;
    for (i = 0; i < size && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;

    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        free(buffer);
        return 1;
    }

    if (read > 0 && buffer[read - 1] == '\n') {
        buffer[read - 1] = '\0';
    }

    replace_chars(buffer, (size_t)read);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}