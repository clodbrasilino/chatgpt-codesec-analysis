#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_keith_number(int num) {
    if (num < 10) {
        return false;
    }

    int temp = num;
    int num_digits = 0;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    int *sequence = (int *)malloc(num_digits * sizeof(int));
    if (sequence == NULL) {
        exit(EXIT_FAILURE);
    }

    temp = num;
    int index = num_digits - 1;
    while (temp > 0) {
        sequence[index] = temp % 10;
        index--;
        temp /= 10;
    }

    while (true) {
        int next_val = 0;
        for (int i = 0; i < num_digits; i++) {
            next_val += sequence[i];
        }

        if (next_val == num) {
            free(sequence);
            return true;
        }

        if (next_val > num) {
            free(sequence);
            return false;
        }

        for (int i = 0; i < num_digits - 1; i++) {
            sequence[i] = sequence[i + 1];
        }
        sequence[num_digits - 1] = next_val;
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num = atoi(argv[1]);
    if (num <= 0) {
        fprintf(stderr, "Error: Input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (is_keith_number(num)) {
        printf("%d is a Keith number.\n", num);
    } else {
        printf("%d is not a Keith number.\n", num);
    }

    return EXIT_SUCCESS;
}