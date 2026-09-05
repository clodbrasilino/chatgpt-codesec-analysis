#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_even(int num) {
    return (num & 1) == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return EXIT_SUCCESS;
}