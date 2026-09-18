#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t find_lobb_number(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    uint64_t a = 1, b = 1;
    for (int i = 2; i <= n; ++i) {
        uint64_t next = 2 * a + b;
        if (next < a || next < b) break;
        a = b;
        b = next;
    }
    return a;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = find_lobb_number(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The %d-th Lobb number is: %llu\n", n, result);

    return 0;
}