#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_char(const char *str) {
    unsigned char sum = 0;
    size_t len = strlen(str);
    size_t i;

    for (i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }

    return (char)sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Error: Input string cannot be empty\n");
        return EXIT_FAILURE;
    }

    char result = find_char(argv[1]);
    printf("%c\n", result);

    return EXIT_SUCCESS;
}