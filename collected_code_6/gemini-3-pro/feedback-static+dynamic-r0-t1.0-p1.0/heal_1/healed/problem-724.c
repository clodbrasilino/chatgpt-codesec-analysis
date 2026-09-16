#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 100000

int calculate_digit_sum(int base, int power) {
    if (base < 0 || power < 0) {
        return -1;
    }

    if (power == 0) {
        return 1;
    }

    if (base == 0) {
        return 0;
    }

    int* num = (int*)calloc(MAX_ARRAY_SIZE, sizeof(int));
    if (num == NULL) {
        return -1; 
    }

    num[0] = 1;
    int num_size = 1;

    for (int i = 0; i < power; i++) {
        int carry = 0;
        for (int j = 0; j < num_size; j++) {
            int prod = num[j] * base + carry;
            num[j] = prod % 10;
            carry = prod / 10;
        }

        while (carry > 0) {
            if (num_size >= MAX_ARRAY_SIZE) {
                free(num);
                return -1; 
            }
            num[num_size] = carry % 10;
            carry = carry / 10;
            num_size++;
        }
    }

    int sum = 0;
    for (int i = 0; i < num_size; i++) {
        sum += num[i];
    }

    free(num);
    return sum;
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <base> <power>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long base_l = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || base_l < 0 || base_l > 10000) {
        printf("Invalid base.\n");
        return EXIT_FAILURE;
    }

    long power_l = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || power_l < 0 || power_l > 10000) {
        printf("Invalid power.\n");
        return EXIT_FAILURE;
    }

    int base = (int)base_l;
    int power = (int)power_l;

    int sum = calculate_digit_sum(base, power);

    if (sum == -1) {
        printf("Error calculating digit sum.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", sum);

    return EXIT_SUCCESS;
}