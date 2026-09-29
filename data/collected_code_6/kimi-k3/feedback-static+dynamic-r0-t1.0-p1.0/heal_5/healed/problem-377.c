#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char c) {
    if (str == NULL) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] != c) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void) {
    char *buffer = NULL;
    char target;
    int scan_result;
    size_t buffer_size = BUFFER_SIZE;
    ssize_t chars_read;

    printf("Enter a string: ");
    
    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    chars_read = getline(&buffer, &buffer_size, stdin);
    if (chars_read == -1) {
        free(buffer);
        return 1;
    }

    if (chars_read > 0 && buffer[chars_read - 1] == '\n') {
        buffer[chars_read - 1] = '\0';
    }

    printf("Enter character to remove: ");
    scan_result = scanf(" %c", &target);
    if (scan_result != 1) {
        free(buffer);
        return 1;
    }

    remove_char(buffer, target);

    printf("Result: %s\n", buffer);

    free(buffer);
    return 0;
}