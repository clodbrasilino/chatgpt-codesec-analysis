#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_hex_even(const char *hex_str);

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    size_t i = 0;
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        i = 2;
    }

    if (hex_str[i] == '\0') {
        return -1;
    }

    char last_char = '\0';
    while (hex_str[i] != '\0') {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
        last_char = (char)tolower((unsigned char)hex_str[i]);
        i++;
    }

    if (last_char == '0' || last_char == '2' || last_char == '4' || 
        last_char == '6' || last_char == '8' || last_char == 'a' || 
        last_char == 'c' || last_char == 'e') {
        return 1;
    }

    return 0;
}

int main(void) {
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 1;
    }

    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';

    if (length == 0 && ch == EOF) {
        free(buffer);
        return 1;
    }

    int result = is_hex_even(buffer);
    free(buffer);

    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid\n");
        return 1;
    }

    return 0;
}