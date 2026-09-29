#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int is_hex_even(const char *hex_str) {
    size_t len;
    size_t i;
    int value;

    if (hex_str == NULL) {
        errno = EINVAL;
        return -1;
    }

    len = strlen(hex_str);
    if (len == 0) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            errno = EINVAL;
            return -1;
        }
    }

    if (hex_str[0] == '0' && len > 1 && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        if (len == 2) {
            errno = EINVAL;
            return -1;
        }
        value = isdigit((unsigned char)hex_str[len - 1]) ? hex_str[len - 1] - '0' : toupper((unsigned char)hex_str[len - 1]) - 'A' + 10;
    } else {
        value = isdigit((unsigned char)hex_str[len - 1]) ? hex_str[len - 1] - '0' : toupper((unsigned char)hex_str[len - 1]) - 'A' + 10;
    }

    return (value % 2 == 0) ? 1 : 0;
}

int main(int argc, char const * const argv[]) {
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hex_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = is_hex_even(argv[1]);

    if (errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return EXIT_SUCCESS;
}