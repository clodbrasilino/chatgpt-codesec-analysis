#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int a = 10;
    int b = 3;
    
    if (argc == 3) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    
    int result = find_remainder(a, b);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}