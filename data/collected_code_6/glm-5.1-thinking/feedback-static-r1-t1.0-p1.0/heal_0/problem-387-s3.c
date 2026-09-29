#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int is_hex_odd(const char *hex_str) {
    if (hex_str == NULL) {
        return -1;
    }
    
    char *endptr = NULL;
    errno = 0;
    unsigned long long value = strtoull(hex_str, &endptr, 16);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == hex_str) {
        return -1;
    }

    if (*endptr != '\0') {
        return -1;
    }

    return (int)(value % 2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hex_number>\n", argv[0]);
        return 1;
    }

    int result = is_hex_odd(argv[1]);
    if (result < 0) {
        fprintf(stderr, "Invalid hexadecimal input\n");
        return 1;
    }

    printf("%s\n", result == 0 ? "Even" : "Odd");

    return 0;
}