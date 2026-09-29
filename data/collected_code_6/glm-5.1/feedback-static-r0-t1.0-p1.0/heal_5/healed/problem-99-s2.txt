#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char *decimal_to_binary(int n) {
    int bits = 0;
    int temp = n;

    if (n == 0) {
        bits = 1;
    } else {
        if (n < 0) {
            bits = sizeof(int) * CHAR_BIT;
        } else {
            while (temp != 0) {
                temp /= 2;
                bits++;
            }
        }
    }

    char *result = malloc(bits + 1);
    if (result == NULL) {
        return NULL;
    }

    result[bits] = '\0';

    if (n == 0) {
        result[0] = '0';
        return result;
    }

    unsigned int unum = (unsigned int)n;
    for (int i = bits - 1; i >= 0; i--) {
        result[i] = (unum % 2) + '0';
        unum /= 2;
    }

    return result;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: not a valid decimal integer\n");
        return 1;
    }

    int n = (int)val;
    char *binary = decimal_to_binary(n);

    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", binary);
    free(binary);

    return 0;
}