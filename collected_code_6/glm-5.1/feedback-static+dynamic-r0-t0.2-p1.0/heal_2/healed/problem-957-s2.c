#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
}

int main(int argc, char const * const * argv) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    int pos = get_rightmost_set_bit(n);
    printf("%d\n", pos);
    return EXIT_SUCCESS;
}