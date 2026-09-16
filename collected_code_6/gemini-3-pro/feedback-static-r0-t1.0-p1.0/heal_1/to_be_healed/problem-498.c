#include <stdio.h>
#include <stdlib.h>

unsigned int find_gcd(unsigned int a, unsigned int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned int temp;
    
    if (a == 0 && b == 0) {
        return 0;
    }
    
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive integer1> <positive integer2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 1 || val2 < 1) {
        fprintf(stderr, "Error: Both arguments must be positive integers.\n");
        return EXIT_FAILURE;
    }

    unsigned int num1 = (unsigned int)val1;
    unsigned int num2 = (unsigned int)val2;

    unsigned int gcd = find_gcd(num1, num2);

    printf("%u\n", gcd);

    return EXIT_SUCCESS;
}