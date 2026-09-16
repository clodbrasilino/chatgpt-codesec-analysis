#include <stdio.h>
#include <stdlib.h>

int find_min(int a, int b);

int find_min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    int num1;
    int num2;
    int min_val;
    int scan_result;

    scan_result = scanf("%d %d", &num1, &num2);
    if (scan_result != 2) {
        return EXIT_FAILURE;
    }

    min_val = find_min(num1, num2);

    if (printf("%d\n", min_val) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}