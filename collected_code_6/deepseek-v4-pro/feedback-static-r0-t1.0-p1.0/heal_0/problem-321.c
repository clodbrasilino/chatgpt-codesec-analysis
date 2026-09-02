#include <stdio.h>
#include <stdlib.h>

long long demlo_number(int n) {
    if (n <= 0) {
        return 0;
    }
    long long result = 0;
    long long term = 0;
    for (int i = 1; i <= n; i++) {
        term = term * 10 + 1;
        result += term;
    }
    return result * result;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (num < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", demlo_number(num));
    return EXIT_SUCCESS;
}