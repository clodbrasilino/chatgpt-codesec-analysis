#include <stdio.h>
#include <stdlib.h>

int differ_at_one_bit_position(int a, int b) {
    int xor_result = a ^ b;
    if (xor_result == 0) {
        return 0;
    }
    if ((xor_result & (xor_result - 1)) == 0) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int res = differ_at_one_bit_position((int)val1, (int)val2);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}