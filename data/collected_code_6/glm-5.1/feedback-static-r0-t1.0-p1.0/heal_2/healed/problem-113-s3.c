#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int is_integer(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t i = 0;

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    if (str[i] == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
        i++;
    }

    return 1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (is_integer(argv[1])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}