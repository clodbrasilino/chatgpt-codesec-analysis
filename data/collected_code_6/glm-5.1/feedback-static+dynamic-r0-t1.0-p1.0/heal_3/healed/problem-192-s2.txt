#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    int has_letter = 0;
    int has_number = 0;
    size_t len = strnlen(str, max_len);

    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            has_letter = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = check_string(argv[1], 4096);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}