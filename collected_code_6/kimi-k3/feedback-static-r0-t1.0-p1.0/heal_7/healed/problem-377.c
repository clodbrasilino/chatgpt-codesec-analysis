#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

void remove_char(char *str, size_t size, char c) {
    if (str == NULL || size == 0) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;

    while (read_idx < size && str[read_idx] != '\0') {
        if (str[read_idx] != c) {
            if (write_idx < size - 1) {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
        }
        read_idx++;
    }

    str[write_idx] = '\0';
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char target;
    int scan_result;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }
    }

    printf("Enter character to remove: ");
    scan_result = scanf(" %c", &target);
    if (scan_result != 1) {
        return 1;
    }

    remove_char(buffer, sizeof(buffer), target);

    printf("Result: %s\n", buffer);

    return 0;
}