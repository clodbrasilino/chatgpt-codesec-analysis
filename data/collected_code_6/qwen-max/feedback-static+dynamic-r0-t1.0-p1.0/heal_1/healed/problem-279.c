#include <stdio.h>
#include <stdint.h>

int64_t nth_decagonal_number(int64_t n) {
    int64_t result = 4 * n * n - 3 * n;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = nth_decagonal_number(n);
    printf("The %ldth decagonal number is: %ld\n", n, result);
    return 0;
}