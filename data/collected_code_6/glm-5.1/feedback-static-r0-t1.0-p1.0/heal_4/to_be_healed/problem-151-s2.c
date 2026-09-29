#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int are_coprime(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    return gcd(abs(a), abs(b)) == 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int a, b;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) > 11 || strlen(argv[2]) > 11) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%11d", &a) != 1 || sscanf(argv[2], "%11d", &b) != 1) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    if (are_coprime(a, b)) {
        printf("%d and %d are co-prime\n", a, b);
    } else {
        printf("%d and %d are not co-prime\n", a, b);
    }
    return EXIT_SUCCESS;
}