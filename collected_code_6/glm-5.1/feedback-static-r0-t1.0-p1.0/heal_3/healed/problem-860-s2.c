#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ends_with_alphanumeric(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }

    if (isalnum((unsigned char)ptr[-1])) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (ends_with_alphanumeric(argv[1])) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}