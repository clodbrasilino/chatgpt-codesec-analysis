#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int jumpsRequired(int d, int l) {
    if (d == 0) {
        return 0;
    }
    if (d < 0) {
        d = -d;
    }
    if (l <= 0) {
        return -1;
    }
    if (d % l == 0) {
        return d / l;
    }
    if (d < l) {
        return 2;
    }
    return (d / l) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int d, l;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <distance> <jump_length>\n", argv[0]);
        return EXIT_FAILURE;
    }
    d = atoi(argv[1]);
    l = atoi(argv[2]);
    int result = jumpsRequired(d, l);
    if (result == -1) {
        printf("Invalid jump length\n");
    } else {
        printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}