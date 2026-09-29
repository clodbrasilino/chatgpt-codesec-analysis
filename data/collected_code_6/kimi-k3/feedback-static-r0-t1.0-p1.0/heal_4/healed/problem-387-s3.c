#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

bool is_hex_even(const char *hex_str, size_t max_len, bool *is_valid)
{
    size_t len = 0;
    size_t start_idx;
    char last_char;
    int last_digit;

    if (hex_str == NULL || is_valid == NULL || max_len == 0) {
        return false;
    }

    *is_valid = false;

    while (len < max_len && hex_str[len] != '\0') {
        len++;
    }

    if (len == max_len && hex_str[len] != '\0') {
        return false;
    }

    start_idx = 0;

    if (len > 2 && hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start_idx = 2;
    }

    if (start_idx >= len) {
        return false;
    }

    for (size_t i = start_idx; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return false;
        }
    }

    last_char = hex_str[len - 1];

    if (last_char >= '0' && last_char <= '9') {
        last_digit = last_char - '0';
    } else if (last_char >= 'A' && last_char <= 'F') {
        last_digit = last_char - 'A' + 10;
    } else if (last_char >= 'a' && last_char <= 'f') {
        last_digit = last_char - 'a' + 10;
    } else {
        return false;
    }

    *is_valid = true;
    return (last_digit % 2 == 0);
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_len;
    bool is_valid = false;
    bool is_even = false;

    printf("Enter a hexadecimal number: ");
    
    read_len = getline(&input, &input_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        read_len--;
    }

    if (read_len == 0) {
        fprintf(stderr, "Invalid hexadecimal number\n");
        free(input);
        return 1;
    }

    is_even = is_hex_even(input, (size_t)read_len + 1, &is_valid);

    free(input);

    if (!is_valid) {
        fprintf(stderr, "Invalid hexadecimal number\n");
        return 1;
    }

    if (is_even) {
        printf("The hexadecimal number is even\n");
    } else {
        printf("The hexadecimal number is odd\n");
    }

    return 0;
}