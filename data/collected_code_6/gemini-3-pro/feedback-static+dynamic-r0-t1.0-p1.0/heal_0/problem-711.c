#include <stdio.h>
#include <stdlib.h>

int checkProduct(int num) {
    if (num < 0) {
        num = -num;
    }

    if (num == 0) {
        return 1;
    }

    int evenProduct = 1;
    int oddProduct = 1;
    int position = 1;

    while (num > 0) {
        int digit = num % 10;
        if (position % 2 == 0) {
            evenProduct *= digit;
        } else {
            oddProduct *= digit;
        }
        num /= 10;
        position++;
    }

    if (position == 2) {
        return 0;
    }

    return (evenProduct == oddProduct) ? 1 : 0;
}

int main() {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (checkProduct(num)) {
        printf("Equal\n");
    } else {
        printf("Not Equal\n");
    }

    return EXIT_SUCCESS;
}