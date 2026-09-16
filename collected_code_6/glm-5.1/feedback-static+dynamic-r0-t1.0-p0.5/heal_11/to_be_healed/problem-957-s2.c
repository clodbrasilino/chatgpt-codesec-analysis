#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(int n) {
    if (n == 0) {
        return -1;
    }
    int rightmost_bit = n & (-n);
    int pos = 0;
    while (rightmost_bit > 1) {
        rightmost_bit >>= 1;
        pos++;
    }
    return pos;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int num;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &num) != 1) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int pos = get_rightmost_set_bit_position(num);
    if (pos == -1) {
        printf("0\n");
    } else {
        printf("%d\n", pos);
    }
    return EXIT_SUCCESS;
}