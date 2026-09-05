#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

int main(int argc, char *argv[]) {
    int a = 10;
    int b = 3;
    int remainder = find_remainder(a, b);
    printf("%d\n", remainder);
    return 0;
}