#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main() {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strnlen(input, sizeof(input) - 1);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        replace_chars(input, len);
        printf("Modified string: %s\n", input);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    return 0;
}