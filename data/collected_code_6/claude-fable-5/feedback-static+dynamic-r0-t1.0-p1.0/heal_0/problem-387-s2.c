#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_valid_hex(const char *str)
{
    size_t len;
    size_t i;
    size_t start = 0;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    if (len > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        start = 2;
    }

    if (start >= len) {
        return 0;
    }

    for (i = start; i < len; i++) {
        if (!isxdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}

int hex_is_even(const char *hex_str)
{
    size_t len;
    char last;
    int digit_value;

    len = strlen(hex_str);
    last = hex_str[len - 1];

    if (last >= '0' && last <= '9') {
        digit_value = last - '0';
    } else if (last >= 'a' && last <= 'f') {
        digit_value = last - 'a' + 10;
    } else {
        digit_value = last - 'A' + 10;
    }

    return (digit_value % 2) == 0;
}

int main(void)
{
    char buffer[128];
    size_t len;

    printf("Enter a hexadecimal number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (!is_valid_hex(buffer)) {
        fprintf(stderr, "Invalid hexadecimal number\n");
        return EXIT_FAILURE;
    }

    if (hex_is_even(buffer)) {
        printf("%s is even\n", buffer);
    } else {
        printf("%s is odd\n", buffer);
    }

    return EXIT_SUCCESS;
}