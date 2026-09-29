#include <stdio.h>

unsigned long long find_demlo(unsigned int n) {
    unsigned long long num = 1;
    for (unsigned int i = 0; i < n; i++) {
        num = (num * 10) + 1;
    }

    return num * num;
}

int main() {
    unsigned int n = 0;
    unsigned long long demlo = 0;

    printf("Enter the value for n: ");
    if (scanf("%u", &n) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        return 1;
    }
    demlo = find_demlo(n);

    printf("The Demlo number for n=%u is %llu\n", n, demlo);
    return 0;
}