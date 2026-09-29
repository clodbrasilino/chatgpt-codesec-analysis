#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    int n = (int)val;
    int pos = get_rightmost_set_bit(n);

    printf("%d\n", pos);

    return EXIT_SUCCESS;
}