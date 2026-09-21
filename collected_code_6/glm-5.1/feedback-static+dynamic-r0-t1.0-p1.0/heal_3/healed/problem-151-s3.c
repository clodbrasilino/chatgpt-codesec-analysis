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
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return gcd(a, b) == 1;
}

int main(int argc, char * const argv[const]) {
    int a, b;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (strlen(argv[1]) > 11 || sscanf(argv[1], "%d", &a) != 1) {
        fprintf(stderr, "Invalid first argument\n");
        return EXIT_FAILURE;
    }
    
    if (strlen(argv[2]) > 11 || sscanf(argv[2], "%d", &b) != 1) {
        fprintf(stderr, "Invalid second argument\n");
        return EXIT_FAILURE;
    }
    
    if (are_coprime(a, b)) {
        printf("%d and %d are coprime\n", a, b);
    } else {
        printf("%d and %d are not coprime\n", a, b);
    }
    
    return EXIT_SUCCESS;
}