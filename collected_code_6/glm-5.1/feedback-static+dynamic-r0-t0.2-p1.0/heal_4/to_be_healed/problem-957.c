#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return 0;
    }
    int mask = n & (-n);
    int pos = 0;
    while (mask >>= 1) {
        pos++;
    }
    return pos + 1;
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
    int pos = get_rightmost_set_bit(num);
    if (pos == 0) {
        printf("0\n");
    } else {
        printf("%d\n", pos);
    }
    return EXIT_SUCCESS;
}