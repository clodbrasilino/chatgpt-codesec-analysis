#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply_and_update(int *result, int *size, int base) {
    int carry = 0;
    for (int i = 0; i < *size; i++) {
        int prod = result[i] * base + carry;
        result[i] = prod % 10;
        carry = prod / 10;
    }
    while (carry) {
        result[*size] = carry % 10;
        carry /= 10;
        (*size)++;
    }
}

int sum_of_digits_of_power(int base, int power) {
    if (base < 0 || power < 0) {
        return -1;
    }

    int capacity = 10000;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    result[0] = 1;
    int size = 1;

    for (int i = 0; i < power; i++) {
        multiply_and_update(result, &size, base);
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += result[i];
    }

    free(result);
    return sum;
}

int main(void) {
    int base = 2;
    int power = 15;
    
    int sum = sum_of_digits_of_power(base, power);
    
    if (sum != -1) {
        printf("%d\n", sum);
    }
    
    return 0;
}