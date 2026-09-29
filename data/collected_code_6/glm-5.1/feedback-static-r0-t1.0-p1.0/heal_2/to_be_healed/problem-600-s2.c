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
        return 1;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return 1;
    }

    int num = (int)val;
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}