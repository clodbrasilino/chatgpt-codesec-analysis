#include <stdio.h>

int divide_first_even_odd(int *list, int size) {
    int even = 0;
    int odd = 0;

    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            even = list[i];
            break;
        }
    }

    for (int i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            odd = list[i];
            break;
        }
    }

    if (odd == 0) {
        return 0;
    }

    return even / odd;
}

int main() {
    int list[] = {2, 4, 6, 8, 10, 3, 5, 7};

    int result = divide_first_even_odd(list, sizeof(list) / sizeof(list[0]));

    printf("Division: %d\n", result);

    return 0;
}