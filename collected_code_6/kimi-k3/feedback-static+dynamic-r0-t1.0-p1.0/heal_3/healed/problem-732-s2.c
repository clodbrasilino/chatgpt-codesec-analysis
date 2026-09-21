#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
        }
        str++;
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

    if (read > 0) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }

    replace_chars(buffer);
    printf("%s\n", buffer);

    free(buffer);
    return 0;
}