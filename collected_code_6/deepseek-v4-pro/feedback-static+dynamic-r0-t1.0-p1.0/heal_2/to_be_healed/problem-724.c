#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply_by_base(char *result, int base, int len) {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int product = (result[i] - '0') * base + carry;
        result[i] = (product % 10) + '0';
        carry = product / 10;
    }
    while (carry > 0) {
        result[len] = (carry % 10) + '0';
        carry /= 10;
        len++;
    }
    result[len] = '\0';
}

int sum_of_digits(int base, int exponent) {
    if (base < 0 || exponent < 0) {
        return -1;
    }
    if (base == 0) {
        return exponent == 0 ? 1 : 0;
    }
    if (exponent == 0) {
        return 1;
    }

    char *result = (char *)malloc(10000 * sizeof(char));
    if (result == NULL) {
        return -1;
    }

    result[0] = '1';
    result[1] = '\0';

    for (int i = 0; i < exponent; i++) {
        multiply_by_base(result, base, (int)strlen(result));
    }

    int sum = 0;
    for (int i = 0; result[i] != '\0'; i++) {
        sum += result[i] - '0';
    }

    free(result);
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", argv[0]);
        return 1;
    }

    int base = atoi(argv[1]);
    int exponent = atoi(argv[2]);

    if (base < 0 || exponent < 0) {
        fprintf(stderr, "Error: Base and exponent must be non-negative.\n");
        return 1;
    }

    int result = sum_of_digits(base, exponent);
    if (result < 0) {
        fprintf(stderr, "Error: Calculation failed or invalid input.\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}