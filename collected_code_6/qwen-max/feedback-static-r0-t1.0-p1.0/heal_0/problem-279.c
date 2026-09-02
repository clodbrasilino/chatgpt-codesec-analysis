#include <stdio.h>

long nth_decagonal_number(long n) {
    return 4 * n * n - 3 * n;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long result = nth_decagonal_number(n);
    printf("The %ldth decagonal number is: %ld\n", n, result);
    return 0;
}