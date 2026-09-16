#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int x, int y) {
    int xor_val = x ^ y;
    int distance = 0;

    while (xor_val != 0) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }

    return distance;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer1> <integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    int num1 = (int)strtol(argv[1], &endptr1, 10);
    int num2 = (int)strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input: Please provide integer values.\n");
        return EXIT_FAILURE;
    }

    int distance = hamming_distance(num1, num2);
    printf("Hamming distance: %d\n", distance);

    return EXIT_SUCCESS;
}