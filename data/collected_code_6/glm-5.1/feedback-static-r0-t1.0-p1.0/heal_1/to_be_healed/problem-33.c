#include <stdio.h>
#include <stdlib.h>

char* decimal_to_binary(int n) {
    if (n < 0) {
        return NULL;
    }

    char* binary_str = malloc(33);
    if (binary_str == NULL) {
        return NULL;
    }

    if (n == 0) {
        binary_str[0] = '0';
        binary_str[1] = '\0';
        return binary_str;
    }

    int index = 31;
    binary_str[32] = '\0';

    while (n > 0) {
        binary_str[index] = (n % 2) + '0';
        n /= 2;
        index--;
    }

    int start = index + 1;
    int length = 32 - start;

    if (start > 0) {
        for (int i = 0; i <= length; i++) {
            binary_str[i] = binary_str[start + i];
        }
    }

    return binary_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_number>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Must be a non-negative integer.\n");
        return 1;
    }

    char *result = decimal_to_binary((int)val);
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return 1;
    }

    printf("%s\n", result);
    
    free(result);
    result = NULL;

    return 0;
}