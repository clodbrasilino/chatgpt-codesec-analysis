#include <stdio.h>
#include <stdbool.h>

bool checkProduct(int num) {
    int odd = 1, even = 1, count = 1;
    while (num) {
        if (count % 2 == 0)
            even *= num % 10;
        else
            odd *= num % 10;
        num /= 10;
        count++;
    }
    return even == odd;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (checkProduct(num))
        printf("Product of digits at even and odd places are equal.\n");
    else
        printf("Product of digits at even and odd places are not equal.\n");
    return 0;
}