#include <stdio.h>
#include <stdlib.h>

char *decimal_to_binary(int n) {
    if (n == 0) {
        char *bin = malloc(2);
        if (bin == NULL) {
            exit(EXIT_FAILURE);
        }
        bin[0] = '0';
        bin[1] = '\0';
        return bin;
    }

    int temp = n;
    size_t length = 0;

    while (temp > 0) {
        length++;
        temp /= 2;
    }

    char *bin = malloc(length + 1);
    if (bin == NULL) {
        exit(EXIT_FAILURE);
    }

    bin[length] = '\0';

    while (n > 0) {
        bin[--length] = (n % 2) + '0';
        n /= 2;
    }

    return bin;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val < 0) {
        fprintf(stderr, "Only non-negative integers are supported\n");
        return EXIT_FAILURE;
    }

    char *result = decimal_to_binary((int)val);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return EXIT_SUCCESS;
}