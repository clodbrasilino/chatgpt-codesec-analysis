#include <stdio.h>

int find_ASCII_sum(char str[]) {
    int i, sum = 0;
    for(i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum;
}

int main() {
    char myStr[] = "Hello, world!";

    int sum = find_ASCII_sum(myStr);

    printf("Sum of ASCII values: %d\n", sum);

    return 0;
}