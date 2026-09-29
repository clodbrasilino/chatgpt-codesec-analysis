#include <stdio.h>
#include <stdlib.h>

int nth_polite_number(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    int bit_count = 0;
    int temp = n;
    while (temp > 0) {
        if (temp & 1) {
            bit_count++;
        }
        temp >>= 1;
    }
    return n + bit_count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    int result = nth_polite_number(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}