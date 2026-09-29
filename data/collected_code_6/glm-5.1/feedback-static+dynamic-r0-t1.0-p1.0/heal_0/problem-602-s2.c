#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

char find_first_repeated(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len < 2) {
        return '\0';
    }

    int count[ASCII_SIZE] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] == 1) {
            return str[i];
        }
        count[c]++;
    }

    return '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = find_first_repeated(argv[1]);

    if (result != '\0') {
        printf("%c\n", result);
        return EXIT_SUCCESS;
    } else {
        printf("No repeated character found\n");
        return EXIT_FAILURE;
    }
}