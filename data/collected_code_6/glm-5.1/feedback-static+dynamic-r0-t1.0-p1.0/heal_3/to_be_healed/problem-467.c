#include <stdio.h>
#include <stdlib.h>

int decimal_to_octal(int decimal) {
    if (decimal < 0) {
        return -1;
    }
    if (decimal == 0) {
        return 0;
    }
    int octal = 0;
    int place = 1;
    while (decimal > 0) {
        int remainder = decimal % 8;
        octal += remainder * place;
        place *= 10;
        decimal /= 8;
    }
    return octal;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    int decimal = (int)val;
    int octal = decimal_to_octal(decimal);
    if (octal == -1) {
        fprintf(stderr, "Conversion error\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", octal);
    return EXIT_SUCCESS;
}