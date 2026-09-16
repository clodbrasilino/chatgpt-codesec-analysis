#include <stdio.h>
#include <stdlib.h>

unsigned long long pell_number(unsigned int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long prev = 0, curr = 1;
    for (unsigned int i = 2; i <= n; ++i) {
        unsigned long long next = 2 * curr + prev;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main() {
    unsigned int n = 0;
    printf("Enter the value of n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = pell_number(n);
    printf("The %uth Pell number is: %llu\n", n, result);

    return EXIT_SUCCESS;
}