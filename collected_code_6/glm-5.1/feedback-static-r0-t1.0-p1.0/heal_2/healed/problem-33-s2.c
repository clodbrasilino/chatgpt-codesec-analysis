#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char* decimal_to_binary(int n) {
    if (n == 0) {
        char* result = malloc(2);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int temp = n;
    size_t bits = 0;
    while (temp != 0) {
        temp /= 2;
        bits++;
    }

    char* result = malloc(bits + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t index = bits;
    result[index] = '\0';

    while (n != 0) {
        index--;
        result[index] = (n % 2) + '0';
        n /= 2;
    }

    return result;
}

int main(int argc, char const* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;
    char* binary = decimal_to_binary(num);

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", binary);
    free(binary);

    return EXIT_SUCCESS;
}