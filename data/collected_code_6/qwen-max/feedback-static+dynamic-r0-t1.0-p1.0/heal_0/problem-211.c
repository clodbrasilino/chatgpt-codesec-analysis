#include <stdio.h>
#include <stdbool.h>

bool is_oth_nth_bit_set(int num, int o, int n) {
    return (num & (1 << o)) && (num & (1 << n));
}

int count_numbers_with_oth_nth_bit_set(const int *numbers, int length, int o, int n) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (is_oth_nth_bit_set(numbers[i], o, n)) {
            count++;
        }
    }
    return count;
}

int main() {
    int numbers[] = {3, 7, 15, 26, 9, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int o = 2;
    int n = 1;

    int result = count_numbers_with_oth_nth_bit_set(numbers, length, o, n);
    printf("Count of numbers with %d and %d bits set: %d\n", o, n, result);

    return 0;
}