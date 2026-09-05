#include <stdio.h>
#include <stdlib.h>

int find_gcd(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (val1 <= 0 || val2 <= 0 || val1 > __INT_MAX__ || val2 > __INT_MAX__ || *endptr1 != '\0' || *endptr2 != '\0') {
        return EXIT_FAILURE;
    }
    int a = (int)val1;
    int b = (int)val2;
    int gcd = find_gcd(a, b);
    printf("%d\n", gcd);
    return EXIT_SUCCESS;
}