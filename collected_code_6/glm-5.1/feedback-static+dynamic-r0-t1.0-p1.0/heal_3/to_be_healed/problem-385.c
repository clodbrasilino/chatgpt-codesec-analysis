#include <stdio.h>
#include <stdlib.h>

int perrin(int n) {
    if (n == 1) {
        return 3;
    } else if (n == 2) {
        return 0;
    } else if (n == 3) {
        return 2;
    } else {
        return perrin(n - 2) + perrin(n - 3);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", perrin(n));
    return EXIT_SUCCESS;
}