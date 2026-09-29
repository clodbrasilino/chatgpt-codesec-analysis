#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) {
        if (a < 0) {
            return -a;
        }
        return a;
    }
    return gcd(b, a % b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int a, b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &a) != 1 || sscanf(argv[2], "%d", &b) != 1) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", gcd(a, b));
    return EXIT_SUCCESS;
}