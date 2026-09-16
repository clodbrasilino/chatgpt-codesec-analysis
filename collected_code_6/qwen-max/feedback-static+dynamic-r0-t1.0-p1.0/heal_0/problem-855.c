#include <stdio.h>
#include <stdbool.h>

bool check_even_parity(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return (count % 2) == 0;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    bool is_even_parity = check_even_parity(number);
    if (is_even_parity) {
        printf("The number has even parity.\n");
    } else {
        printf("The number does not have even parity.\n");
    }
    return 0;
}