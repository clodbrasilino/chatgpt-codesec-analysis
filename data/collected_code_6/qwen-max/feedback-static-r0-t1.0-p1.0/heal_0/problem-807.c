#include <stdio.h>
#include <stdbool.h>

int find_first_odd(int *numbers, int length) {
    for (int i = 0; i < length; i++) {
        if (numbers[i] % 2 != 0) {
            return numbers[i];
        }
    }
    return -1;
}

int main() {
    int numbers[] = {2, 4, 6, 8, 10, 11, 14};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int first_odd = find_first_odd(numbers, length);
    if (first_odd != -1) {
        printf("First odd number: %d\n", first_odd);
    } else {
        printf("No odd number found.\n");
    }
    return 0;
}