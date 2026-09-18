#include <stdio.h>

int count_equal_numbers(int a, int b, int c) {
    int count = 0;

    if(a == b) count++;
    if(a == c) count++;
    if(b == c) count++;

    return count ? (count + 1) : 0;
}

int main() {
    int a, b, c;

    printf("Enter three integers: \n");
    scanf("%d %d %d", &a, &b, &c);

    printf("The count of equal numbers is %d.\n", count_equal_numbers(a, b, c));

    return 0;
}