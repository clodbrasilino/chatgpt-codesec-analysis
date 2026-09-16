#include <stdio.h>
#include <stdlib.h>

int find_factorial_divisible(int x) {
    if (x <= 0) {
        return -1;
    }
    int n = 1;
    long long factorial = 1;
    while (factorial % x != 0) {
        n++;
        if (n > 20) {
            return -1;
        }
        factorial *= n;
    }
    return n;
}

int main(int argc, char * const argv[]) {
    int x;
    if (argc != 2) {
        return 1;
    }
    x = atoi(argv[1]);
    if (x <= 0) {
        return 1;
    }
    int result = find_factorial_divisible(x);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}