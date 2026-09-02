#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int is_valid_range(int low, int high) {
    return low > 0 && high >= low;
}

int find_two_numbers_with_lcm_in_range(int low, int high, int *num1, int *num2) {
    if (!is_valid_range(low, high) || num1 == NULL || num2 == NULL) {
        return 0;
    }

    for (int a = low; a <= high; a++) {
        for (int b = a + 1; b <= high; b++) {
            int current_lcm = lcm(a, b);
            if (current_lcm >= low && current_lcm <= high) {
                *num1 = a;
                *num2 = b;
                return 1;
            }
        }
    }

    return 0;
}

int main(void) {
    int low, high;
    int num1, num2;

    printf("Enter lower bound: ");
    if (scanf("%d", &low) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%d", &high) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_range(low, high)) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    if (find_two_numbers_with_lcm_in_range(low, high, &num1, &num2)) {
        printf("Found numbers %d and %d with LCM %d in range [%d, %d]\n",
               num1, num2, lcm(num1, num2), low, high);
        return EXIT_SUCCESS;
    }

    printf("No such pair exists in range [%d, %d]\n", low, high);
    return EXIT_SUCCESS;
}