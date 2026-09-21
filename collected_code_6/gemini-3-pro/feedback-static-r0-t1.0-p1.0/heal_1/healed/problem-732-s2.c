#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

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
    char *input = NULL;
    size_t len = 0;
    ssize_t bytes_read;

    bytes_read = getline(&input, &len, stdin);

    if (bytes_read != -1) {
        if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
            input[bytes_read - 1] = '\0';
        }

        replace_chars(input);
        
        printf("%s\n", input);
    }

    free(input);
    input = NULL;

    return 0;
}