#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(int n) {
    if (n < 10) {
        return false;
    }

    int temp = n;
    int num_digits = 0;
    
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    int *sequence = (int *)malloc(num_digits * sizeof(int));
    if (sequence == NULL) {
        return false;
    }

    temp = n;
    for (int i = num_digits - 1; i >= 0; i--) {
        sequence[i] = temp % 10;
        temp /= 10;
    }

    while (1) {
        int next_val = 0;
        for (int i = 0; i < num_digits; i++) {
            next_val += sequence[i];
        }

        if (next_val == n) {
            free(sequence);
            return true;
        }

        if (next_val > n) {
            free(sequence);
            return false;
        }

        for (int i = 0; i < num_digits - 1; i++) {
            sequence[i] = sequence[i + 1];
        }
        sequence[num_digits - 1] = next_val;
    }
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_keith_number(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}