#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char first_non_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int *counts = (int *)calloc(256, sizeof(int));
    if (counts == NULL) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char index = (unsigned char)str[i];
        counts[index]++;
    }

    char result = '\0';
    for (size_t i = 0; i < len; i++) {
        unsigned char index = (unsigned char)str[i];
        if (counts[index] == 1) {
            result = str[i];
            break;
        }
    }

    free(counts);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char result = first_non_repeated_char(argv[1]);
    if (result == '\0') {
        printf("No non-repeated character found.\n");
    } else {
        printf("%c\n", result);
    }

    return EXIT_SUCCESS;
}