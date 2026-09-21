#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char c) {
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        if (*str == ' ') {
            *str = c;
        }
        str++;
    }
}

int main(int argc, char *argv[]) {
    char buffer[256];
    const char *input = "Replace blank spaces with any character";
    size_t buffer_size = sizeof(buffer);
    size_t input_len = strnlen(input, buffer_size);
    if (input_len >= buffer_size) {
        return 1;
    }
    snprintf(buffer, buffer_size, "%s", input);
    printf("Original: %s\n", buffer);
    replace_spaces(buffer, '-');
    printf("Modified: %s\n", buffer);
    return 0;
}