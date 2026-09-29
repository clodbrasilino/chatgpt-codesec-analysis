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

int main(int argc, char * const argv[const]) {
    int a, b;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }
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