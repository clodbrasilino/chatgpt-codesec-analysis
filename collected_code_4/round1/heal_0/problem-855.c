#include <stdio.h>

int check_even_parity(unsigned int n) {
    int parity = 0;
    while (n) {
        parity = ~parity;
        n = n & (n - 1);
    }
    return parity;
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);
    if(check_even_parity(n) == 0)
        printf("Number has even parity\n");
    else
        printf("Number has odd parity\n");
    return 0;
}