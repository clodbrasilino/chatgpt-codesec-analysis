#include <stdio.h>
#include <stdlib.h>

int find_max(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, char *argv[]) {
    int num1 = 10;
    int num2 = 20;
    int maximum;

    maximum = find_max(num1, num2);

    if (printf("Maximum: %d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}