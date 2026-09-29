#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 20, got <no output>
  *  test case 2 failed: expected -10, got <no output>
  *  test case 1 failed: expected 19, got <no output>
  */

int max_of_two(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
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

    if (sscanf(argv[1], "%d", &a) != 1) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%d", &b) != 1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", max_of_two(a, b));

    return EXIT_SUCCESS;
}