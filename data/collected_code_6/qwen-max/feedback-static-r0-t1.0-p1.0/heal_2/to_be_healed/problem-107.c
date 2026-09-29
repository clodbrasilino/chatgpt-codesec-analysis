#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_hexadecimal(const char *s) {
    for (; *s; s++) {
        if (!((*s >= '0' && *s <= '9') || (*s >= 'a' && *s <= 'f') || (*s >= 'A' && *s <= 'F'))) {
            return false;
        }
    }
    return true;
}

int count_hex_numbers(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%d", i);
        if (is_hexadecimal(buffer)) {
            count++;
        }
    }
    return count;
}

int main() {
    int start = 10;
    int end = 100;
    int hex_count = count_hex_numbers(start, end);
    printf("Number of hexadecimal numbers in the range: %d\n", hex_count);
    return 0;
}