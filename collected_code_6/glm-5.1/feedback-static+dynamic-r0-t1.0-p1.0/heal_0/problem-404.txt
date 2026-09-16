#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char *argv[]) {
    int a = 10;
    int b = 20;
    int result = min(a, b);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}