#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_last_digit(int n) {
    int abs_n;
    if (n == INT_MIN) {
        abs_n = INT_MAX + 1;
    } else if (n < 0) {
        abs_n = -n;
    } else {
        abs_n = n;
    }
    return abs_n % 10;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    int last_digit = find_last_digit(n);
    printf("%d\n", last_digit);
    return EXIT_SUCCESS;
}