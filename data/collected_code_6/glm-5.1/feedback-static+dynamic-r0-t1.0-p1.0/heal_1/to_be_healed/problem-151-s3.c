#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;
    while (b != 0) {
        temp = b;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int a, b;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &a) != 1) {
        fprintf(stderr, "Invalid first argument\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[2], "%d", &b) != 1) {
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