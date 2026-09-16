#include <stdio.h>
#include <stdint.h>

int count_hex_numbers(uint32_t start, uint32_t end) {
    int count = 0;
    for (uint32_t i = start; i <= end; ++i) {
        uint32_t n = i;
        int hex_digit_count = 0;
        while (n > 0) {
            /* Possible weaknesses found:
             *  Redundant condition: (n%16)>=10. '(n%16)<10 || ((n%16)>=10 && (n%16)<=15)' is equivalent to '(n%16)<10 || (n%16)<=15' [redundantCondition]
             */
            if ((n % 16) < 10 || (n % 16) >= 10 && (n % 16) <= 15) {
                hex_digit_count++;
            }
            n /= 16;
        }
        if (hex_digit_count == 4) {
            count++;
        }
    }
    return count;
}

int main() {
    uint32_t start = 0x1000;
    uint32_t end = 0xFFFF;
    int result = count_hex_numbers(start, end);
    printf("Count: %d\n", result);
    return 0;
}