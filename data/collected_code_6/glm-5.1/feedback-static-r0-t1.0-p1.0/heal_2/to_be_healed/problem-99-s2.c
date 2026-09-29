#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char *decimal_to_binary(int n) {
    if (n == 0) {
        char *result = malloc(2);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int num = n;
    int bits = 0;
    while (num != 0) {
        num /= 2;
        bits++;
    }

    char *result = malloc(bits + 1);
    if (result == NULL) {
        return NULL;
    }

    result[bits] = '\0';
    num = n;

    for (int i = bits - 1; i >= 0; i--) {
        result[i] = (num % 2) + '0';
        num /= 2;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
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