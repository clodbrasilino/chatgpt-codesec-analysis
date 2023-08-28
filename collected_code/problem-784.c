#include <stdio.h>

int findProduct(int numbers[], int length) {
    int even = -1, odd = -1;
    int product = 0;

    for (int i = 0; i < length; i++) {
        if (numbers[i] % 2 == 0 && even == -1) {
            even = numbers[i];
        } else if (numbers[i] % 2 != 0 && odd == -1) {
            odd = numbers[i];
        }

        if (even != -1 && odd != -1) {
            product = even * odd;
            break;
        }
    }

    return product;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = findProduct(numbers, length);
    printf("Product: %d\n", result);

    return 0;
}