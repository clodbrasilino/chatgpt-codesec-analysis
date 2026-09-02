#include <stdio.h>
#include <stdint.h>

int highest_power_of_two(int n) {
    if (n <= 0) {
        return 0;
    }
    int power = 1;
    while (power * 2 <= n) {
        power *= 2;
    }
    return power;
}

int main() {
    int test_numbers[] = {0, 1, 2, 15, 16, 17, 1023, 1024, 1025};
    for (size_t i = 0; i < sizeof(test_numbers) / sizeof(test_numbers[0]); ++i) {
        printf("The highest power of two less than or equal to %d is: %d\n", 
               test_numbers[i], highest_power_of_two(test_numbers[i]));
    }
    return 0;
}